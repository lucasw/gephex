#include "controleditor.h"

#include <stdexcept>
#include <cassert>
#include <iostream>

#include <qmessagebox.h>
#include <qpopupmenu.h>

#include "interfaces/imodelcontrolreceiver.h"

#include "guimodel/controlmodel.h"
#include "guimodel/controlvaluedispatcher.h"

#include "typeviewfactory.h"
#include "controlwidget.h"

namespace gui
{

  ControlEditor::ControlEditor(QWidget* parent, const char* name, WFlags fl,
			       ControlModel& cModel, 
			       IModelControlReceiver& model,
			       ControlValueDispatcher& disp)
    : QWidget(parent,name,fl),  m_controller(&cModel), 
    m_model(&model), m_factory(new TypeViewFactory()),
    currentNodeID(-1), currentInputIndex(-1), currentWidgetType(""),
    currentControl(0), m_controlValueDispatcher(&disp)
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
    try {
      con = m_factory->getConstructor(widgetType);
    } catch(std::runtime_error& e) {
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
	
    this->controlWidgetMoved(cWidget,QPoint(clickedPos.x(), clickedPos.y()));
	
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
    which->move(p.x(),p.y());
  }

  void ControlEditor::controlDeleted(int controlID)
  {
    std::map<int,ControlWidget*>::iterator cewit = widgets.find(controlID);
    if(cewit == widgets.end())
      {
	//TODO
	std::cerr << "Das Control gibts nicht, das gelöscht wurde"
		  << std::endl;

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

  void ControlEditor::selectWidgetType(const std::string& name,
				       const std::string& type,int nodeID,
				       int inputIndex,
				       const ParamMap& params,
				       const QPoint& pos)
  {
    currentNodeID = nodeID;
    currentInputIndex = inputIndex;
    currentName = name;
    currentParams = params;

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
	QPopupMenu *popme = new QPopupMenu(0, "pop");
		
	int id = 0;
	for (TypeViewFactory::TypeViewInfoList::const_iterator
	       i = infos.begin();
	     i != infos.end(); ++i)
	  {
	    //  std::cout << "Inserting " << i->getName()
	    //      << ", id = " << id << std::endl;
	    popme->insertItem(i->getName().c_str(),id);
	    id2Identifier[id] = i->getID();
	    ++id;
	  }

	connect(popme,SIGNAL(activated(int)),
		this,SLOT(widgetTypeSelected(int)));
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

  void ControlEditor::widgetTypeSelected(int wType)
  {
    currentWidgetType = id2Identifier[wType];
  }

  void ControlEditor::mousePressEvent(QMouseEvent* e)
  {
    if (e->button() == LeftButton)
      {
	try
	  {
		  		  
	    if (currentNodeID != -1 && currentInputIndex != -1)
	      {
		Point clickedPos( e->pos().x(), e->pos().y() );
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
  }

  void ControlEditor::controlWidgetMoved(ControlWidget* n, const QPoint& pos)
  {
    /*    QWidget* label = n->getLabel();
    label->move(QPoint(pos.x(), pos.y() - label->height()));
    label->show();*/
    n->move(pos);
  }

  void ControlEditor::controlWidgetReleased(ControlWidget* n,const QPoint& pos)
  {
    try
      {
	m_controller->moveControl(n->controlID(),
				  Point(pos.x(),pos.y()));
      }
    catch (std::exception& err)
      {
	QMessageBox::information( 0, "Error", err.what() );
      }
  }

  void ControlEditor::openPopup(ControlWidget* which, const QPoint& pos)
  {
    QPopupMenu *popme = new QPopupMenu(0, "pop");
    popme->insertItem("Kill",CONTROLELEMENTWIDGET_KILL);
	
    currentControl = which;
    connect(popme,SIGNAL(activated(int)),this,
	    SLOT(controlPopupActivated(int)));

    popme->popup(which->mapToGlobal(pos));
  }

  void ControlEditor::controlPopupActivated(int action)
  {
    switch(action)
      {
      case CONTROLELEMENTWIDGET_KILL:
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
	break;
      default:
	QMessageBox::information( 0, "Error", "what?" );
      }
  }

} // end of namespace gui
