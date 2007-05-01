/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "controleditor.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

#include <QtGui/QMessageBox>
#include <QtGui/QMenu>
#include <QtGui/QMouseEvent>

#include "mouseover.h"

#include "interfaces/imodelcontrolreceiver.h"

#include "guimodel/controlmodel.h"
#include "guimodel/controlvaluedispatcher.h"

#include "typeviewfactory.h"
#include "controlwidget.h"

#include "labelwidget.h"

#include "base/askforstringdialog.h"

namespace gui
{

  //------------------------------------------------------------------------

  ControlEditor::ControlEditor(QWidget* parent,
			       ControlModel& cModel, 
			       IModelControlReceiver& model,
                               const utils::AutoPtr<ControlValueDispatcher>& disp,
			       const std::string& media_path)
    : QWidget(parent),
      m_controller(&cModel), 
      m_model(&model),
      m_factory(new TypeViewFactory(media_path)),
      currentNodeID(-1),
      currentInputIndex(-1),
      currentWidgetType(""),
      currentControl(0),
      m_controlValueDispatcher(disp)
  {
  }

  ControlEditor::~ControlEditor()
  {
    delete m_factory;
  }


  void ControlEditor::controlChanged(int nodeID, int inputIndex,
				     const utils::Buffer& b)
  {
    m_model->setInputValue(nodeID, inputIndex, b);
  }

  void ControlEditor::controlAdded(int controlID, const std::string& name,
				   int nodeID,int inputIndex, 
				   const std::string& widgetType,
				   const ParamMap& params)
  {
    TypeViewConstructor* con = 0;
    try
      {
        con = m_factory->getConstructor(widgetType);
      }
    catch(std::runtime_error& e)
      {
        //TODO
        std::cerr << e.what() << std::endl;
        return;
    }
    ControlWidget*
      cWidget = new ControlWidget(this, name, controlID,nodeID,
				  inputIndex,params, con);

    if (cWidget == 0)
      {
	//TODO
	std::cerr << "Could not create ControlWidget at " 
		  << "ControlEditor::controlAdded()" 
		  << std::endl;
	return;
      }
    
    widgets[controlID] = cWidget;

    QObject::connect(cWidget,
		     SIGNAL(valueChanged(int,int,const utils::Buffer&)),
		     this,
		     SLOT(controlChanged(int,int,const utils::Buffer&)));
    
    connect(cWidget,SIGNAL(moved(ControlWidget*,const QPoint&)),
	    this,SLOT(controlWidgetMoved(ControlWidget*,const QPoint&)));
	
    connect(cWidget,SIGNAL(released(ControlWidget*,const QPoint&)),
	    this,SLOT(controlWidgetReleased(ControlWidget*,const QPoint&)));
	
    connect(cWidget,SIGNAL(beenRightClicked(ControlWidget*, const QPoint&)),
	    this,SLOT(openPopup(ControlWidget*, const QPoint&)));

    m_controlValueDispatcher->registerValueReceiver(nodeID,inputIndex,
						    *cWidget);

    this->controlWidgetMoved(cWidget, 
                             mapToGlobal(QPoint(clickedPos.x(),
                                                clickedPos.y())));

    // add a mouseover object to detect wether the mouse is over the
    // controlwidget
    
    MouseOver* mo = new MouseOver(cWidget);
    connect(mo, SIGNAL(mouseOver(QWidget*)),
            this, SLOT(mouseOverControl(QWidget*)));

    cWidget->show();
  }

  void ControlEditor::controlMoved(int controlID, const Point& p)
  {
    std::map<int,ControlWidget*>::iterator cewit = widgets.find(controlID);
    if(cewit == widgets.end())
      {
	//TODO
	std::cerr << "No such control at ControlEditor::controlMoved()"
		  << std::endl;
	return;
      }
    ControlWidget* which = cewit->second;
    which->move(std::max(0, p.x()),
                std::max(0, p.y()));
  }

  void ControlEditor::controlDeleted(int controlID)
  {
    std::map<int,ControlWidget*>::iterator cewit = widgets.find(controlID);
    if(cewit == widgets.end())
      {
	//TODO
	std::cerr << "No such control at ControlEditor::controlDeleted()\n";
	return;
      }

    ControlWidget* cWidget = cewit->second;

    m_controlValueDispatcher->unregisterValueReceiver(cWidget->nodeID(),
						      cWidget->inputIndex(),
						      *cWidget);

    delete cWidget;
    widgets.erase(cewit);
  }

  void ControlEditor::controlRenamed(int controlID, const std::string& name)
  {
    std::map<int,ControlWidget*>::iterator cewit = widgets.find(controlID);
    if(cewit == widgets.end())
      {
	//TODO:
	std::cerr << "Das Control gibts nicht, "
		  << "ControlEditor::controlRenamed()" << std::endl;
	return;
      }

    cewit->second->setName(name);
  }

  void ControlEditor::labelAdded(int labelID, const std::string& text)
  {
    //    std::cout << "label " << labelID << " added: '" << text << "'\n";

    LabelWidget* lWidget = new LabelWidget(this, labelID, text);

    if (lWidget == 0)
      {
	//TODO
	std::cerr << "Could not create LabelWidget at " 
		  << "ControlEditor::labelAdded()" 
		  << std::endl;
	return;
      }
    
    labels.insert(std::make_pair(labelID, lWidget));

    connect(lWidget,SIGNAL(moved(LabelWidget*,const QPoint&)),
	    this, SLOT(labelWidgetMoved(LabelWidget*,const QPoint&)));
	
    connect(lWidget,SIGNAL(released(LabelWidget*,const QPoint&)),
	    this, SLOT(labelWidgetReleased(LabelWidget*,const QPoint&)));
	
    connect(lWidget,SIGNAL(beenRightClicked(LabelWidget*, const QPoint&)),
	    this, SLOT(openLabelPopup(LabelWidget*, const QPoint&)));

    this->labelWidgetMoved(lWidget,
                           mapToGlobal(QPoint(clickedPos.x(),
                                              clickedPos.y())));
	
    lWidget->show();
  }

  void ControlEditor::labelMoved(int labelID, const Point& p)
  {
    //    std::cout << "label " << labelID << " moved\n";

    std::map<int,LabelWidget*>::iterator lewit = labels.find(labelID);
    if(lewit == labels.end())
      {
	//TODO
	std::cerr << "No such label at ControlEditor::labelMoved()"
		  << std::endl;
	return;
      }
    LabelWidget* which = lewit->second;

    which->move(std::max(0, p.x()),
                std::max(0, p.y()));
  }

  void ControlEditor::labelDeleted(int labelID)
  {
    //    std::cout << "label " << labelID << " deleted\n";

    std::map<int, LabelWidget*>::iterator lewit = labels.find(labelID);
    if(lewit == labels.end())
      {
	//TODO
	std::cerr << "No such label at ControlEditor::labelDeleted()"
		  << std::endl;

	return;
      }

    delete lewit->second;
    labels.erase(lewit);
  }

  void ControlEditor::selectWidgetType(const std::string& name,
				       const std::string& type,int nodeID,
				       int inputIndex,
				       const ParamMap& params,
				       const QPoint& pos)
  {
    currentNodeID     = nodeID;
    currentInputIndex = inputIndex;
    currentName       = name;
    currentParams     = params;

    if (currentNodeID == -1)
      return;

    TypeViewFactory::TypeViewInfoList infos 
      =  m_factory->getCompatibleViews(type);

    //    std::cout << "Fetched list of compatible views..." << std::endl;
    if (infos.empty())
      {
	QMessageBox::information(0,"Fehler","Kein passendes Control!");
      }
    else
      {
	//std::cout << "List is not empty..." << std::endl;
	QMenu *popme = new QMenu("pop");
		
	for (TypeViewFactory::TypeViewInfoList::const_iterator
	       i = infos.begin();
	     i != infos.end(); ++i)
	  {
	    QAction* ac = new QAction(i->getName().c_str(), popme);
	    ac->setData(QVariant(i->getID().c_str()));

	    popme->addAction(ac);
	  }

	connect(popme,SIGNAL(triggered(QAction*)),
		this,SLOT(actionTriggeredSlot(QAction*)));
	popme->popup(pos);
      }
  }

  void ControlEditor::deleteControl(int nodeID,int inputIndex)
  {
    std::map<int,ControlWidget*>::const_iterator it = widgets.begin();

    for (; it != widgets.end(); ++it)
      {
	int controlID = it->first;
	ControlWidget* cWidget = it->second;

	if (cWidget->nodeID() == nodeID && cWidget->inputIndex() == inputIndex)
	  {
	    m_controller->delControl(controlID);
	    break;
	  }
      }
  }

  void ControlEditor::actionTriggeredSlot(QAction* action)
  {
    currentWidgetType = action->data().toString().toUtf8().constData();
  }

  void ControlEditor::mousePressEvent(QMouseEvent* e)
  {
    clickedPos = Point( e->pos().x(), e->pos().y() );

    if (e->button() == Qt::LeftButton)
      {
	try
	  {
	    if (currentNodeID != -1 && currentInputIndex != -1)
	      {
		m_controller->addControl(clickedPos,currentName,currentNodeID,
					 currentInputIndex,currentWidgetType,
					 currentParams);

		currentNodeID = -1;
		currentInputIndex = -1;
	      }
	  }
	catch (std::exception& err)
	  {
	    QMessageBox::information( 0, "Error", err.what() );
	  }
      }
    else if (e->button() == Qt::RightButton)
      {
        QMenu* popme = new QMenu("contextpop");
	
	QAction* labelAction = new QAction("Add Label", popme);

        popme->addAction(labelAction);
	
        connect(labelAction,SIGNAL(triggered()),this,
                SLOT(addLabelSlot()));

        popme->popup(e->globalPos());        
      }
  }

  void ControlEditor::controlWidgetMoved(ControlWidget* n, const QPoint& pos)
  {
    /*    QWidget* label = n->getLabel();
    label->move(QPoint(pos.x(), pos.y() - label->height()));
    label->show();*/
    n->move(mapFromGlobal(pos));
  }

  void ControlEditor::controlWidgetReleased(ControlWidget* n,const QPoint& pos)
  {
    QPoint p = mapFromGlobal(pos);
    try
      {
	m_controller->moveControl(n->controlID(),
				  Point(p.x(),p.y()));
      }
    catch (std::exception& err)
      {
	QMessageBox::information( 0, "Error", err.what() );
      }
  }

  void ControlEditor::openPopup(ControlWidget* which, const QPoint& pos)
  {
    QMenu *popme = new QMenu("pop");

    QAction* killAction = new QAction("Kill", popme);
    popme->addAction(killAction);
	
    currentControl = which;
    connect(killAction, SIGNAL(triggered()),
	    this, SLOT(killControlSlot()));

    popme->popup(pos);
  }


  void ControlEditor::labelWidgetMoved(LabelWidget* n, const QPoint& pos)
  {
    /*    QWidget* label = n->getLabel();
    label->move(QPoint(pos.x(), pos.y() - label->height()));
    label->show();*/
    n->move(mapFromGlobal(pos));
  }

  void ControlEditor::labelWidgetReleased(LabelWidget* n,const QPoint& pos)
  {
    QPoint p = mapFromGlobal(pos);
    try
      {
	m_controller->moveLabel(n->id(),
                                Point(p.x(),p.y()));
      }
    catch (std::exception& err)
      {
	QMessageBox::information( 0, "Error", err.what() );
      }
  }

  void ControlEditor::openLabelPopup(LabelWidget* which, const QPoint& pos)
  {
    QMenu* popme = new QMenu("labelpop");

    QAction* killAction = new QAction("Kill", popme);
    popme->addAction(killAction);
	
    currentLabel = which;
    connect(killAction,SIGNAL(triggered()),
	    this, SLOT(killLabelSlot()));

    popme->popup(pos);
  }

  void ControlEditor::killControlSlot()
  {
    int controlID = currentControl->controlID();
    try
      {
	m_controller->delControl(controlID);
      }
    catch (std::exception& err)
      {
	QMessageBox::information( 0, "Error", err.what() );
      }
  }

  void ControlEditor::killLabelSlot()
  {
    int labelID = currentLabel->id();
    try
      {
	m_controller->delLabel(labelID);
      }
    catch (std::exception& err)
      {
	QMessageBox::information( 0, "Error", err.what() );
      }
  }

  void ControlEditor::addLabelSlot()
  {
    const std::string
      text = AskForStringDialog::open(0, "New Label",
				      "Enter label text");

    m_controller->addLabel(clickedPos, text);
  }


  void ControlEditor::mouseOverControl(QWidget* w)
  {
    ControlWidget* cw = dynamic_cast<ControlWidget*>(w);
    if (cw == 0)
      {
        QMessageBox::information( 0, "Error", "mouseOverControl fu'ed up" );
        return;
      }

    emit inputSelected(cw->nodeID(), cw->inputIndex());
  }

} // end of namespace gui
