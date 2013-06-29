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

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <list>
#include <map>
#include <string>

#include <QtGui/QWidget>

#include "interfaces/imodulestatisticsreceiver.h"
#include "interfaces/imodelstatusreceiver.h"

#include "guimodel/igraphview.h"
#include "guimodel/icontrolconnectview.h"
#include "guimodel/point.h"

#include "utils/autoptr.h"

#include "base/picmanager.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QToolButton;

class IModelControlReceiver;
class IErrorReceiver;

namespace gui
{

  class ModuleInfo;
  class NodeWidget;
  class InputPlugWidget;
  class OutputPlugWidget;
  class PlugWidget;
  class ConnectionWidget;
  class GraphModel;
  class ControlValueDispatcher;
  class IModuleInfoBaseStation;
  class IPropertyDescription;
  class KeyboardManager;


  class GraphEditor : public QWidget, 
		      public IGraphView,
		      public IControlConnectView,
		      public IModuleStatisticsReceiver,
		      public IModelStatusReceiver
  {
    Q_OBJECT

  public:
    typedef std::map<std::string, std::string> ParamMap;
    GraphEditor(QWidget* parent,
		GraphModel& contr,
		const IModuleInfoBaseStation&,
		const utils::AutoPtr<ControlValueDispatcher>& dispatcher_,
		IModelControlReceiver&,
		KeyboardManager* kbManager,
		IErrorReceiver& log,
		const std::string& media_path);

    ~GraphEditor();
	

    //IModuleStatisticsReceiver
    virtual void modExecTimeSignal(int nodeID, double time);

    // IGraphView	
    virtual void moduleAdded(const std::string& moduleClassName,int modID) ;
    virtual void modulesConnected(int moduleID1,int outputIndex,
				  int moduleID2,int inputIndex) ;
    virtual void modulesDisconnected( int moduleID,int inputIndex);
    virtual void moduleDeleted(int moduleID);
    //virtual void graphChanged(const std::string& name);
    virtual void moduleMoved(int moduleID,const Point&);

    // IControlConnectView

    virtual void controlConnected(int nodeID, int inputIndex);
    virtual void controlDisconnected(int nodeID, int inputIndex);

    virtual void editGraphChanged( const std::string& graphID,
				   const std::string& snapID );

  public slots:

    void redrawLine(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput(const InputPlugWidget*,const QPoint& to);
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);
    void openPopup(InputPlugWidget*);
    void openPopup(NodeWidget*, const QPoint&);
    void openPopup(ConnectionWidget*,const QPoint&);

    void nodeWidgetMoved(NodeWidget*, const QPoint&);
    void nodeWidgetClicked(NodeWidget*);
    void nodeWidgetReleased(NodeWidget* n,const QPoint& pos);

    void propertySlot();
    void internalsSlot();
    void killNodeSlot();

    void connectToControlSlot();
    void removeControlSlot();
    void disconnectSlot();

    void killConnectionSlot();

    void mouseOverNode(const NodeWidget*);
    void mouseOverInputPlug(const InputPlugWidget*);
    void mouseOverOutputPlug(const OutputPlugWidget*);

    void moduleClassSelected(const std::string&);

    void setDrawModuleInfo(bool draw){m_drawmoduleinfo=draw;}

    // used to show the user to which input a control is connected
    void highlightInput(int moduleID, int inputIndex);

  signals:
    void createControl(const std::string& name,const std::string& type,
		       int nodeID,int inputIndex,
		       const ParamMap& params, const QPoint&);

    void deleteControl(int nodeID,int inputIndex);

    void statusText(const std::string&);
    void displayProperties(const IPropertyDescription& pd);
    void undisplayProperties();

    /**
     * This signal is emitted when the model tells the graph editor,
     * that the edit graph has changed.
     */
    void newEditGraph( const std::string& graphID,
		       const std::string& snapID);


  protected:
    QHBoxLayout* Frame3Layout;
    virtual void mousePressEvent(QMouseEvent*);
    virtual void paintEvent ( QPaintEvent * );


  private:
    void connectionRequest(const InputPlugWidget* in,
			   const OutputPlugWidget* out);

    void decConnectionCount(PlugWidget* plug);
    void incConnectionCount(PlugWidget* plug);

  private slots:
    void timer_fired();

  private:
    std::map<int, NodeWidget*> nodes;
    
    typedef std::map<std::pair<int, int>, ConnectionWidget*> ConnectionMap;
    ConnectionMap connections;

    std::pair<int, int> selectedConnectionPair;
    
    QPoint m_currentFrom;
    QPoint m_currentTo;

    QPoint clickedPos;
    std::string currentModuleClassName;

    // der node bzw der input fuer den ein popup menue geoeffnet wurde:
    NodeWidget* currentNode;
    InputPlugWidget* currentInput;  
    InputPlugWidget* highlightedInput;

    GraphModel* m_controller;
    PicManager m_picmanager;

    const InputPlugWidget* getInputPlugByPos(const QPoint& to) const;
    const OutputPlugWidget* getOutputPlugByPos(const QPoint& to) const;

    std::map<const InputPlugWidget*,bool> hasControl;

    std::map<const PlugWidget*,int> numConnections;

    const IModuleInfoBaseStation* infos;

    utils::AutoPtr<ControlValueDispatcher> dispatcher;

    IModelControlReceiver& model;

    KeyboardManager* m_kbManager;

    IErrorReceiver& m_log;
    bool m_drawmoduleinfo;

    int m_property_id;

    std::string m_media_path;

    unsigned int m_tick_count;
    unsigned int m_last_highlight;
  };

} // end of namespace gui

#endif // GRAPHWIDGET_H
