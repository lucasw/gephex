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

#include <QtGui/QPainter>
#include <QtGui/qframe.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qlayout.h>
#include <QtCore/qvariant.h>
#include <QtGui/qwhatsthis.h>
#include <QtGui/qmessagebox.h>
#include <QtCore/qtimer.h>
#include <QtGui/QMouseEvent>
#include <QtGui/QMenu>

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"
#include "guimodel/graphmodel.h"
#include "guimodel/controlvaluedispatcher.h"

#include "imoduleinfobasestation.h"

#include "nodewidget.h"
#include "inputplugwidget.h"
#include "outputplugwidget.h"
#include "connectionwidget.h"

#include "base/keyboardmanager.h"


#include "utils/buffer.h"


namespace gui
{

  static const int TIMER_MS = 1000;

  GraphEditor::GraphEditor(QWidget* parent,
			   GraphModel& contrl,
			   const IModuleInfoBaseStation& _infos,
			   const utils::AutoPtr<ControlValueDispatcher>& _dispatcher,
			   IModelControlReceiver& mod,
			   KeyboardManager* kbManager,
			   IErrorReceiver& log,
			   const std::string& media_path)
    : QWidget( parent),
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

    NodeWidget* nWidget = new NodeWidget(this,0,modID,
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

    update();
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

    update();
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
    nWidget->move(std::max(0, p.x()),
                  std::max(0, p.y()));
    update();
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

    nWidget->update();
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

    nWidget->update();
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

  namespace
  {
    QRegion CreateRegion(const QPoint& p1, const QPoint& p2)
    {
      const int x_tl = std::min(p1.x(), p2.x());
      const int y_tl = std::min(p1.y(), p2.y());

      const int x_br = std::max(p1.x(), p2.x());
      const int y_br = std::max(p1.y(), p2.y());

      return QRegion(x_tl, y_tl, x_br - x_tl + 2, y_br - y_tl + 1);
    }
  }

  void GraphEditor::redrawLine(const QPoint& from, const QPoint& to)
  {
    update(CreateRegion(from, to) + CreateRegion(m_currentFrom, m_currentTo));

    m_currentFrom = from;
    m_currentTo = to;

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
    m_currentFrom = m_currentTo = QPoint(0, 0);
	
    const OutputPlugWidget* out = getOutputPlugByPos(to);
	
    if (out != 0)
      {
        connectionRequest(in, out);
      }
    else
      {
        update();
      }
  }

  void GraphEditor::connectionRequestFromOutput(const OutputPlugWidget* out, 
						const QPoint& to)
  {
    m_currentFrom = m_currentTo = QPoint(0, 0);
	
    const InputPlugWidget* in = getInputPlugByPos(to);
	
    if (in != 0)
      {
        connectionRequest(in, out);
      }
    else
      {
        update();
      }
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
	emit statusText("the types are incompatible");
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
    n->move(mapFromGlobal(pos));
    update();
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
    QMenu *popme = new QMenu("pop"); //TODO: wird das deleted?

    if (!hasControl[in])
      {
	QAction* connectAction = new QAction("Connect control", popme);
	popme->addAction(connectAction);
	//PLUGWIDGET_CONNECT_TO_CONTROL
	connect(connectAction, SIGNAL(triggered()),
		this, SLOT(connectToControlSlot()));
      }
    else
      {
	QAction* removeAction = new QAction("Remove Control", popme);
	popme->addAction(removeAction);
	//PLUGWIDGET_REMOVE_CONTROL
	connect(removeAction, SIGNAL(triggered()),
		this, SLOT(removeControlSlot()));
      }

    if ((numConnections[in] == 1 && !hasControl[in]) || numConnections[in] > 1)
      {
	QAction* disconnectAction = new QAction("Disconnect", popme);
	popme->addAction(disconnectAction);
	//PLUGWIDGET_DISCONNECT
	connect(disconnectAction, SIGNAL(triggered()),
		this, SLOT(disconnectSlot()));
      }

    currentInput = in;
    popme->popup(in->mapToGlobal(QPoint(0,0)));
  }

  void GraphEditor::openPopup(NodeWidget* which, const QPoint& pos)
  {
    QMenu* popme = new QMenu("pop");

    QAction* propAction      = new QAction("Properties", popme);
    QAction* internalsAction = new QAction("Internals", popme);
    QAction* killAction      = new QAction("Kill", popme);

    popme->addAction(propAction);
    popme->addAction(internalsAction);
    popme->addAction(killAction);

    connect(propAction, SIGNAL(triggered()), this, SLOT(propertySlot()));
    connect(internalsAction, SIGNAL(triggered()), this, SLOT(internalsSlot()));
    connect(killAction, SIGNAL(triggered()), this, SLOT(killNodeSlot()));

    currentNode = which;
    popme->popup(pos);
  }

  void GraphEditor::openPopup(ConnectionWidget* /*which*/, const QPoint& pos)
  {
    QMenu* popme = new QMenu("pop");
    
    QAction* killAction = new QAction("Kill", popme);
    popme->addAction(killAction);
	
    connect(killAction, SIGNAL(triggered()), this, SLOT(killConnectionSlot()));
	
    popme->popup(this->mapToGlobal(pos));
  }

  void GraphEditor::propertySlot()
  {
    if (m_property_id != currentNode->getID())
      {
	emit displayProperties(currentNode->getProperties());
	m_property_id = currentNode->getID();
      }
  }

  void GraphEditor::internalsSlot()
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

  void GraphEditor::killNodeSlot()
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

  void GraphEditor::connectToControlSlot()
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

  void GraphEditor::removeControlSlot()
  {
    emit deleteControl(currentInput->getID(),currentInput->getIndex());
  }

  void GraphEditor::disconnectSlot()
  {
    model.disconnectModules(currentInput->getID(),
			    currentInput->getIndex());

  }

  void GraphEditor::killConnectionSlot()
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
        if(e->button() == Qt::LeftButton)
          {	
            if (selectedConnectionPair != nearest_connection->first)
              {
                selectedConnectionPair = nearest_connection->first;
                update();
              }
          }
        else if (e->button() == Qt::RightButton)
          {
            selectedConnectionPair = nearest_connection->first;
            update();
            this->openPopup(nearest_connection->second, e->pos());
          }
      }
    else if (e->button() == Qt::LeftButton)
      {
	if (selectedConnectionPair != std::make_pair(-1,-1))
	  {
	    selectedConnectionPair = std::make_pair(-1,-1);
	    update();
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
    QPainter mainPainter(this);

    QPen pen1(Qt::SolidLine);
    QPen pen2(Qt::SolidLine);
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


    // Draw current connection attempt
    if (m_currentFrom != QPoint(0,0) &&
        m_currentTo != QPoint(0,0))
      {
        QPen pen(Qt::SolidLine);
        pen.setColor(QColor(20,14,255));
        mainPainter.setPen(pen);
	
        mainPainter.drawLine(m_currentFrom, m_currentTo);
      }
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
      {
        in->highlight();
      }
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
