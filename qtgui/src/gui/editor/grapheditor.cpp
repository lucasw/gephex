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

#include "grapheditor.h"

#include <sstream>
#include <stdexcept>
#include <cassert>

#include <qframe.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qwhatsthis.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qtimer.h>

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"
#include "guimodel/graphmodel.h"
#include "guimodel/controlvaluedispatcher.h"

#include "imoduleinfobasestation.h"

#include "nodewidget.h"
#include "inputplugwidget.h"
#include "outputplugwidget.h"
#include "modulebutton.h"
#include "connectionwidget.h"

#include "base/keyboardmanager.h"


#include "utils/buffer.h"


namespace gui
{

  static const int TIMER_MS = 1000;

  GraphEditor::GraphEditor(QWidget* parent, const char* name, WFlags fl, 
			   GraphModel& contrl,
			   const IModuleInfoBaseStation& _infos,
			   const utils::AutoPtr<ControlValueDispatcher>& _dispatcher,
			   IModelControlReceiver& mod,
			   KeyboardManager* kbManager,
			   IErrorReceiver& log,
			   const std::string& media_path)
    : QWidget( parent, name, fl ),
      nodes(), 
      connections(),
      selectedConnectionPair(-1,-1),
      clickedPos(QPoint(-1,-1)),
      currentModuleClassName(""),
      highlightedInput(0),
      m_controller(&contrl),
      infos(&_infos),
      dispatcher(_dispatcher),
      model(mod),
      m_kbManager(kbManager),
      m_log(log),
      m_drawmoduleinfo(false),
      m_property_id(-1),
      m_media_path(media_path),
      m_tick_count(0),
      m_last_highlight(0)
  {	
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_fired()));
    timer->start(TIMER_MS);
  }

  GraphEditor::~GraphEditor()
  {
    // no need to delete child widgets, Qt does it all for us
  }


  void GraphEditor::moduleAdded(const std::string& moduleClassName,int modID)
  {
    const ModuleInfo& mi = infos->getModuleInfo(moduleClassName);

    NodeWidget* nWidget = new NodeWidget(this,0,0,modID,
					 mi, m_picmanager, dispatcher, model,
					 m_kbManager, m_log,
					 m_media_path);

    // initialise numConnections and hasControl
    std::vector<InputPlugWidget*> ins = nWidget->getInputs();
    for (std::vector<InputPlugWidget*>::const_iterator it = ins.begin();
	 it != ins.end(); ++it)
      {
	numConnections[*it] = 0;
	hasControl[*it] = false;
      }

    std::vector<OutputPlugWidget*> outs = nWidget->getOutputs();
    for (std::vector<OutputPlugWidget*>::const_iterator
	   oit = outs.begin(); oit != outs.end(); ++oit)
      {
	numConnections[*oit] = 0;
      }

    if (clickedPos != QPoint(-1,-1))
      {
	this->m_controller->moveModule(modID,Point(clickedPos.x(),
						   clickedPos.y()));

	nWidget->move(clickedPos.x(), clickedPos.y());
	clickedPos = QPoint(-1,-1);
      }
    nWidget->show();

    connect(nWidget,SIGNAL(clickedLeft(NodeWidget*)),
	    this,SLOT(nodeWidgetClicked(NodeWidget*)));
    connect(nWidget,SIGNAL(moved(NodeWidget*,const QPoint&)),
	    this,SLOT(nodeWidgetMoved(NodeWidget*,const QPoint&)));
    connect(nWidget,SIGNAL(released(NodeWidget*,const QPoint&)),
	    this,SLOT(nodeWidgetReleased(NodeWidget*,const QPoint&)));
	
    connect(nWidget,SIGNAL(beenRightClicked(NodeWidget*, const QPoint&)),
	    this,SLOT(openPopup(NodeWidget*, const QPoint&)));

    connect(nWidget, SIGNAL(beginLineDraw()), this, 
	    SLOT(beginLineDraw()));

    connect(nWidget, SIGNAL(redrawLine(const QPoint&,const QPoint&)),
	    this, SLOT(redrawLine(const QPoint&,const QPoint&)));

    connect(nWidget, SIGNAL(connectionRequestFromInput(const InputPlugWidget*,
						       const QPoint&)),
	    this, SLOT(connectionRequestFromInput(const InputPlugWidget*,
						  const QPoint&)));

    connect(nWidget,
	    SIGNAL(connectionRequestFromOutput(const OutputPlugWidget*,
							const QPoint&)),
	    this, SLOT(connectionRequestFromOutput(const OutputPlugWidget*,
						   const QPoint&)));

    connect(nWidget, SIGNAL(openPopup(InputPlugWidget*)), 
	    this, SLOT(openPopup(InputPlugWidget*)));
	
    connect(nWidget, SIGNAL(mouseOverNode(const NodeWidget*)),
            this, SLOT(mouseOverNode(const NodeWidget*)));

    connect(nWidget, SIGNAL(mouseOverInputPlug(const InputPlugWidget*)), 
	    this, SLOT(mouseOverInputPlug(const InputPlugWidget*)));

    connect(nWidget, SIGNAL(mouseOverOutputPlug(const OutputPlugWidget*)), 
	    this, SLOT(mouseOverOutputPlug(const OutputPlugWidget*)));

	
    nodes[modID] = nWidget;
  }

  void GraphEditor::modulesConnected(int moduleID1,int outputIndex,
				     int moduleID2,int inputIndex)
  {
    std::map<int,NodeWidget*>::const_iterator outIt = nodes.find(moduleID1);
    if (outIt == nodes.end())
      throw std::runtime_error("Module not found at "
			       "GraphEditor::modulesConnected()");
    

    NodeWidget* outWidget = outIt->second; //TODO
    assert(outWidget != 0);

    std::map<int,NodeWidget*>::const_iterator inIt = nodes.find(moduleID2);
    if (inIt == nodes.end())
      throw std::runtime_error("Module not found at "
			       "GraphEditor::modulesConnected()");    

    NodeWidget* inWidget = inIt->second;//TODO
    assert(inWidget != 0);

    InputPlugWidget* in = inWidget->getInputs()[inputIndex];
    this->incConnectionCount(in);

    if (!in->isVisible())
      in->setVisible();

    OutputPlugWidget* out = outWidget->getOutputs()[outputIndex];
    this->incConnectionCount(out);
	
    ConnectionWidget* connWidget = new ConnectionWidget(*in,*out);
  
    connections.insert(ConnectionMap::value_type(std::make_pair(moduleID2,
								inputIndex),
						 connWidget));

    this->repaint();
  }

  void GraphEditor::modulesDisconnected( int moduleID,int inputIndex)
  {
    ConnectionMap::iterator 
      cwit = connections.find(std::make_pair(moduleID, inputIndex));

    if(cwit == connections.end())
      {
	throw std::runtime_error("no such connection at  "
				 "GraphEditor::modulesDisconnected()");
      }

    ConnectionWidget* cWidget = cwit->second;

    this->decConnectionCount(&cWidget->getInPlug());
    this->decConnectionCount(&cWidget->getOutPlug());

    delete cWidget;
    connections.erase(cwit);

    this->repaint();
  }

  void GraphEditor::moduleDeleted(int moduleID)
  {
    std::map<int,NodeWidget*>::iterator nodeIt = nodes.find(moduleID);
    if(nodeIt == nodes.end())
      throw std::runtime_error("GraphEditro::moduleDeleted(): no such module");

    // better safe than sorry: remove highlight
    // (the highlighted input could be deleted)
    if (highlightedInput)
      {
        highlightedInput->removeHighlight();
        highlightedInput = 0;
      }
    currentNode = 0;
    currentInput = 0;
    
    // tell the controleditor that he must not create a control
    emit createControl("", "",
                       -1, 
                       -1, std::map<std::string, std::string>(), QPoint(0,0));

    NodeWidget* nWidget = nodeIt->second;

    // delete the entries in numConnections and hasControl:
    std::vector<InputPlugWidget*> ins = nWidget->getInputs();
    for (std::vector<InputPlugWidget*>::const_iterator it = ins.begin();
	 it != ins.end(); ++it)
      {
	numConnections.erase(*it);
	hasControl.erase(*it);
      }
    std::vector<OutputPlugWidget*> outs = nWidget->getOutputs();
    for (std::vector<OutputPlugWidget*>::const_iterator
	   oit = outs.begin();
	 oit != outs.end(); ++oit)
      {
	numConnections.erase(*oit);
      }


    delete nWidget;
    nodes.erase(nodeIt);
  }


  void GraphEditor::moduleMoved(int nodeID,const Point& p)
  {
    std::map<int,NodeWidget*>::iterator it = nodes.find(nodeID);
    if (it == nodes.end())
      throw std::runtime_error("Modul ex. nicht bei "
			       "GraphEditor::moduleMoved()");

    NodeWidget* nWidget = it->second;
    nWidget->move(p.x(),p.y());
  }

  void GraphEditor::controlConnected(int nodeID, int inputIndex)
  {
    std::map<int,NodeWidget*>::iterator it = nodes.find(nodeID);
    if (it == nodes.end())
      throw std::runtime_error("Modul ex. nicht bei "
			       "GraphEditor::controlConnected()");

    NodeWidget* nWidget = it->second;
    if (inputIndex < 0 || 
        static_cast<unsigned int>(inputIndex) >= nWidget->getInputs().size())
      throw std::runtime_error("Input ex. nicht bei "
			       "GraphEditor::controlConnected()");

    InputPlugWidget* in = nWidget->getInputs()[inputIndex];

    this->incConnectionCount(in);
    hasControl[in] = true;

    if (!in->isVisible())
      in->setVisible();
  }

  void GraphEditor::controlDisconnected(int nodeID, int inputIndex)
  {
    std::map<int,NodeWidget*>::iterator it = nodes.find(nodeID);
    if (it == nodes.end())
      {
	//throw std::runtime_error("Das Modul gibts nicht"
	// "(controlDisconnected)");
	//TODO
	return;
      }

    NodeWidget* nWidget = it->second;

    InputPlugWidget* in = nWidget->getInputs()[inputIndex];

    this->decConnectionCount(in);
    hasControl[in] = false;
  }

  void GraphEditor::modExecTimeSignal(int nodeID, double time)
  {
    std::map<int,NodeWidget*>::iterator it = nodes.find(nodeID);
    if (it == nodes.end())
      throw std::runtime_error("Modul ex. nicht bei "
			       "GraphEditor::modExecTimeSignal()");

    NodeWidget* nWidget = it->second;
    nWidget->setTime(time);    
  }

  void GraphEditor::beginLineDraw()
  {
    oldLineFrom = QPoint(0,0);
    oldLineTo = QPoint(0,0);
  }

  void GraphEditor::redrawLine(const QPoint& from, const QPoint& to)
  {
    mainPainter.begin(this);
	
    QPen pen(SolidLine);
    pen.setColor(QColor(255,255,255));
    mainPainter.setPen(pen);
	
    RasterOp rop = mainPainter.rasterOp();
    mainPainter.setRasterOp(XorROP);
    mainPainter.drawLine(oldLineFrom,oldLineTo);
    mainPainter.drawLine(from, to);
    mainPainter.setRasterOp(rop);
    mainPainter.end();	
	
    oldLineFrom = from;
    oldLineTo = to;
	
    const InputPlugWidget* in = getInputPlugByPos(to);
    if (in != 0)
      {
	mouseOverInputPlug(in);
      }
    const OutputPlugWidget* out = getOutputPlugByPos(to);
    if (out != 0)
      {
	mouseOverOutputPlug(out);
      }
  }

  void GraphEditor::removeOldLine()
  {
    mainPainter.begin(this);
    QPen pen(SolidLine);
    pen.setColor(QColor(255,255,255));
    mainPainter.setPen(pen);
    RasterOp rop = mainPainter.rasterOp();
    mainPainter.setRasterOp(XorROP);
    mainPainter.drawLine(oldLineFrom,oldLineTo);
    mainPainter.setRasterOp(rop);
    mainPainter.end();
  }

  const InputPlugWidget* GraphEditor::getInputPlugByPos(const QPoint& to) const
  {
    const InputPlugWidget* in = 0;
    for (std::map<int,NodeWidget*>::const_iterator i = nodes.begin();
	 i != nodes.end(); ++i)
      {
	NodeWidget* current = i->second;
	in = current->isAtInput(to);
	if (in != 0)
	  return in;
      }
	
    return 0;	
  }

  const OutputPlugWidget* GraphEditor::getOutputPlugByPos(const QPoint& to)
    const
  {
    const OutputPlugWidget* out = 0;
    for (std::map<int,NodeWidget*>::const_iterator i = nodes.begin();
	 i != nodes.end(); ++i)
      {
	NodeWidget* current = i->second;
	out = current->isAtOutput(to);
	if (out != 0)
	  return out;
      }
	  
    return 0;
	  
  }

  void GraphEditor::connectionRequestFromInput(const InputPlugWidget* in, 
					       const QPoint& to)
  {
    removeOldLine();
	
	
    const OutputPlugWidget* out = getOutputPlugByPos(to);
	
    if (out != 0)
      connectionRequest(in, out);
  }

  void GraphEditor::connectionRequestFromOutput(const OutputPlugWidget* out, 
						const QPoint& to)
  {
    removeOldLine();
	
    const InputPlugWidget* in = getInputPlugByPos(to);
	
    if (in != 0)
      connectionRequest(in, out);
  }

  void GraphEditor::connectionRequest(const InputPlugWidget* in,
				      const OutputPlugWidget* out)
  {
    if ((in==0)||(out==0)) 
      {
	//TODO: Fehler anzeigen
	return;
      }
	
    int inputIndex = in->getIndex();
    int outputIndex = out->getIndex();
    int module1ID = out->getID();
    int module2ID = in->getID();

    if (in->getType() != out->getType())
      {
	emit statusText("Typen sind nicht gleich!");
      }
    else
      {
	ConnectionMap::const_iterator 
	  it = connections.find(std::make_pair(module2ID,inputIndex));

	try 
	  {	
	    if (it != connections.end())
	      {
		model.disconnectModules(module2ID,inputIndex);
	      }
	    model.connectModules(module1ID,outputIndex,module2ID,inputIndex);
	  }
	catch (std::exception& err)
	  {
	    m_log.error(err.what() );
	  }
      }
  }

  void GraphEditor::nodeWidgetClicked(NodeWidget* /*n*/)
  {
  }

  void GraphEditor::nodeWidgetMoved(NodeWidget* n, const QPoint& pos)
  {
    repaint(true); //TODO saulahm
    n->move(mapFromGlobal(pos));
  }

  void GraphEditor::nodeWidgetReleased(NodeWidget* n,const QPoint& pos)
  {
    QPoint p = mapFromGlobal(pos);
    try
      {
        m_controller->moveModule(n->getID(),Point(p.x(),p.y()));
      }
    catch (std::exception& err)
      {
	m_log.error(err.what() );
      }

    if (m_property_id != n->getID())
      {
	emit displayProperties(n->getProperties());
	m_property_id = n->getID();
      }
  }

  void GraphEditor::openPopup(InputPlugWidget* in)
  {
    QPopupMenu *popme = new QPopupMenu(0, "pop"); //TODO: wird das deleted?

    if (!hasControl[in])
      popme->insertItem("Connect control",PLUGWIDGET_CONNECT_TO_CONTROL);
    else
      popme->insertItem("Remove control",PLUGWIDGET_REMOVE_CONTROL);

    if ((numConnections[in] == 1 && !hasControl[in]) || numConnections[in] > 1)
      popme->insertItem("Disconnect",PLUGWIDGET_DISCONNECT);

    //    popme->insertItem("Hide Input",PLUGWIDGET_HIDE_INPUT); //TODO
	
    currentInput = in;
    connect(popme,SIGNAL(activated(int)),this,SLOT(inputPopupActivated(int)));
    popme->popup(in->mapToGlobal(QPoint(0,0)));
  }

  void GraphEditor::openPopup(NodeWidget* which, const QPoint& pos)
  {
    QPopupMenu *popme = new QPopupMenu(0, "pop"); //TODO: wird das deleted?
    popme->insertItem("Properties",NODEWIDGET_PROPERTIES);
    popme->insertItem("Internals",NODEWIDGET_INTERNALS);
    popme->insertItem("Kill",NODEWIDGET_KILL);
	
    currentNode = which;
    connect(popme,SIGNAL(activated(int)),this,SLOT(nodePopupActivated(int)));
	
    popme->popup(pos);
  }

  void GraphEditor::openPopup(ConnectionWidget* /*which*/, const QPoint& pos)
  {
    QPopupMenu *popme = new QPopupMenu(0, "pop"); //TODO: wird das deleted?
	
    popme->insertItem("Kill",CONNECTIONWIDGET_KILL);
	
    connect(popme,SIGNAL(activated(int)),this,
	    SLOT(connectionPopupActivated(int)));
	
    popme->popup(this->mapToGlobal(pos));
  }

  void GraphEditor::nodePopupActivated(int action)
  {
    switch(action)
      {
      case NODEWIDGET_KILL:
	{
	  int moduleID = currentNode->getID();
          if (moduleID == m_property_id)
            {
              m_property_id = -1;
              emit undisplayProperties();
            }
	  try
	    {
	      model.deleteModule(moduleID);
	    }
	  catch (std::exception& err)
	    {
	      m_log.error(err.what() );
	    }
	}
	break;
      case NODEWIDGET_PROPERTIES:
	if (m_property_id != currentNode->getID())
	  {
	    emit displayProperties(currentNode->getProperties());
	    m_property_id = currentNode->getID();
	  }
	break;
      case NODEWIDGET_INTERNALS:
	{
          std::ostringstream caption;
          caption << currentNode->moduleClassName() << ":"
                  << currentNode->getID() << " Internals";

          std::ostringstream txt;
          txt << "id:\t" << currentNode->getID() << "\n"
              << "class:\t" << currentNode->moduleClassName() << "\n"
              << "group:\t" << currentNode->group() << "\n"
              << "#in:\t" << currentNode->getInputs().size() << "\n"
              << "#out:\t" << currentNode->getOutputs().size() << "\n"
              << "time:\t" << currentNode->getTime() << " ms\n";

          QMessageBox::about(this, 
                             caption.str().c_str(),
                             txt.str().c_str());
	}
        break;
      default:
	m_log.error("what (nodePopupActivated)?" );
      }
  }

  void GraphEditor::inputPopupActivated(int action)
  {
    switch(action)
      {
      case PLUGWIDGET_CONNECT_TO_CONTROL:
	{
	  std::string name;
	  int nodeID = currentInput->getID();

	  std::map<int,NodeWidget*>::const_iterator it = nodes.find(nodeID);
	  if (it == nodes.end())
	    {
	      name = "FEHLER beim Fehler. GraphEditor::inputPopupActivated()";
	    }
	  else
	    {
	      NodeWidget* n = it->second;
	      name = n->moduleClassName();
	    }
		 
	  name += ':';
	  name += currentInput->getName();
		
	  emit createControl(name,currentInput->getType(),
			     currentInput->getID(), 
			     currentInput->getIndex(),
			     currentInput->getParams(),
			     currentInput->mapToGlobal(QPoint(0,0)));
	}
	break;
      case PLUGWIDGET_REMOVE_CONTROL:
	{
	  emit deleteControl(currentInput->getID(),currentInput->getIndex());
	}
	break;
      case PLUGWIDGET_DISCONNECT:
	{
	  model.disconnectModules(currentInput->getID(),
				  currentInput->getIndex());
	}
	break;
      case PLUGWIDGET_HIDE_INPUT:
	{
	  try
	    {
	      currentInput->setInvisible();
	    }
	  catch (std::runtime_error& e)
	    {
	      m_log.error(e.what() );
	    }
	}
	break;
      default:
	m_log.error("Leider noch nicht "
                    "implementiert. Aber für nen 1000er "
                    "mehr laesst sich da schon was machen..." );
      }
  }

  void GraphEditor::connectionPopupActivated(int action)
  {
    switch(action)
      {
      case CONNECTIONWIDGET_KILL:
	{
	  try
	    {
	      ConnectionMap::const_iterator 
		it = connections.find(selectedConnectionPair);
	      if (it == connections.end())
		{
		  throw std::runtime_error("Internal Compiler error!");
		}
	      ConnectionWidget* cw = it->second;
	      int id = cw->getInPlug().getID();
	      int index = cw->getInPlug().getIndex();
	      model.disconnectModules(id,index);
	    }
	  catch (std::exception& err)
	    {
	      m_log.error(err.what() );
	    }
	}
	break;
      default:
	m_log.error("what (connectionPopupActivated) ?" );
      }
  }

  void GraphEditor::mouseOverNode(const NodeWidget* in)
  {
    std::string msg = "module: ";
    msg += in->group();
    msg += ":";
    msg += in->moduleClassName();
    emit statusText(msg);
  }

  void GraphEditor::mouseOverInputPlug(const InputPlugWidget* in)
  {
    std::string msg = "input: ";
    msg += in->getName();
    msg += " (";
    msg += in->getType();
    msg += ")";
    emit statusText(msg);
  }

  void GraphEditor::mouseOverOutputPlug(const OutputPlugWidget* out)
  {
    std::string msg = "Output: ";
    msg += out->getName();
    msg += " (";
    msg += out->getType();
    msg += ")";
    emit statusText(msg);
  }

  ////////////////////////////////////////////////////////////////////////////
  // events:

  static const double MAX_DIST_FROM_LINE = 5;

  void GraphEditor::mousePressEvent(QMouseEvent* e)
  {
    //grabKeyboard(); //TODO
    //lastMousePos = e->pos();
    double min_dist = 1e10;
    ConnectionMap::iterator nearest_connection = connections.end();

    for (ConnectionMap::iterator i = connections.begin();
	 i != connections.end(); ++i)
      {
        ConnectionWidget* cw = i->second;
        double dist = cw->dist(e->globalPos());
        
        if (dist < MAX_DIST_FROM_LINE && dist < min_dist)
          {
            min_dist = dist;
            nearest_connection = i;
          }
      }

    if (nearest_connection != connections.end())
      {
        if(e->button() == LeftButton)
          {	
            if (selectedConnectionPair != nearest_connection->first)
              {
                selectedConnectionPair = nearest_connection->first;
                repaint(true);
              }
          }
        else if (e->button() == RightButton)
          {
            selectedConnectionPair = nearest_connection->first;
            repaint(true);
            this->openPopup(nearest_connection->second, e->pos());
          }
      }
    else if (e->button() == LeftButton)
      {
	if (selectedConnectionPair != std::make_pair(-1,-1))
	  {
	    selectedConnectionPair = std::make_pair(-1,-1);
	    repaint(true);
	  }
		
	try
	  {
	    this->clickedPos = e->pos();
	    if (currentModuleClassName != "")
	      {
		model.addModule(currentModuleClassName);
		currentModuleClassName = "";
	      }
	  }
	catch (std::exception& err)
	  {
            m_log.error(err.what());
	  }
      }
  }

  void GraphEditor::paintEvent ( QPaintEvent * /*e*/ )
  {
    //    QPixmap buffer(this->height(), this->width());
    //    buffer.fill(this->paletteBackgroundColor());

    mainPainter.begin(this);
    QPen pen1(SolidLine);
    QPen pen2(SolidLine);
    pen1.setColor(QColor(0,0,0));
    pen2.setColor(QColor(0,255,0));
	
    for (ConnectionMap::iterator i = connections.begin();
	 i != connections.end(); ++i)
      {
	std::pair<int,int> id = i->first;
		
	if (id == selectedConnectionPair)
	  mainPainter.setPen(pen2);
	else
	  mainPainter.setPen(pen1);
		
	i->second->draw(this,mainPainter);
      }

    mainPainter.setPen(pen1);

    if (m_drawmoduleinfo)
      {
	for (std::map<int,NodeWidget*>::const_iterator jt = nodes.begin();
	     jt != nodes.end(); ++jt)
	  {
	    NodeWidget* nWidget = jt->second;
	    std::ostringstream msg;
	    msg << nWidget->moduleClassName() << " ("
                << nWidget->getTime() <<")";
	    
	    mainPainter.eraseRect(nWidget->pos().x(),
                                  nWidget->pos().y()-10,
				  40, 10);

	    mainPainter.drawText(nWidget->pos().x(),
                                 nWidget->pos().y()-5,
                                 msg.str().c_str());
	  }
      }
	
    mainPainter.end();

    //    mainPainter.begin(this);

    //    bitBlt(this, 0, 0, &buffer, 0, 0, -1, -1, Qt::CopyROP, false);

    //    mainPainter.end();
  }

  void GraphEditor::highlightInput(int moduleID, int inputIndex)
  {
    InputPlugWidget* in = 0;

    if (moduleID != -1)
      {
        m_last_highlight = m_tick_count;

        std::map<int, NodeWidget*>::const_iterator it = nodes.find(moduleID);
        if (it == nodes.end())
          {
            m_log.error("No such module at GraphEditor::highlightInput()");
            return;
          }

        const NodeWidget* n = it->second;
    
        std::vector<InputPlugWidget*> inputs = n->getInputs();

        if (inputIndex < 0 || (unsigned int) inputIndex >= inputs.size())
          {
            m_log.error("No such input at GraphEditor::highlightInput()");
            return;
          }

        in = inputs[inputIndex];
      }

    if (in != highlightedInput && highlightedInput != 0)
      {
        highlightedInput->removeHighlight();
      }

    highlightedInput = in;

    if (in)
      in->highlight();
  }

  void GraphEditor::timer_fired()
  {
    if (highlightedInput &&
        (m_tick_count - m_last_highlight) * TIMER_MS > 1000)
      {
        highlightedInput->removeHighlight();
        highlightedInput = 0;
      }

    ++m_tick_count;
  }

  void GraphEditor::incConnectionCount(PlugWidget* plug)
  {
    std::map<const PlugWidget*, int>::const_iterator 
      it = numConnections.find(plug);

    if (it == numConnections.end())
      {
	numConnections[plug] = 1;
      }
    else
      {
	++numConnections[plug];
      }

    if (numConnections[plug] > 0)
      plug->setStatus(PlugWidget::PLUG_CONNECTED);
  };

  void GraphEditor::decConnectionCount( PlugWidget* plug)
  {
    std::map<const PlugWidget*, int>::iterator it = numConnections.find(plug);

    if (it == numConnections.end() || it->second <= 0)
      {
	throw std::runtime_error("Lern erstmal Skifahren!!!");
      }

    it->second -= 1;

    if (it->second == 0)
      plug->setStatus(PlugWidget::PLUG_FREE);
  };

  void GraphEditor::moduleClassSelected(const std::string& mName)
  { 
    currentModuleClassName = mName;
  }

  
  void GraphEditor::editGraphChanged( const std::string& graphID,
				      const std::string& snapID )
  {
    emit undisplayProperties();
    clickedPos       = QPoint(-1,-1);
    currentNode      = 0;
    currentInput     = 0;
    highlightedInput = 0;

    selectedConnectionPair = std::make_pair(-1, -1);

    // tell the controleditor that he must not create a control
    emit createControl("", "",
                       -1, 
                       -1, std::map<std::string, std::string>(), QPoint(0,0));
    emit newEditGraph( graphID, snapID );
  }

} //end of namespace gui
