#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <vector>
#include <list>
#include <map>
#include <string>

#include <qwidget.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "interfaces/imodulestatisticsreceiver.h"
#include "interfaces/imodelstatusreceiver.h"

#include "guimodel/igraphview.h"
#include "guimodel/icontrolconnectview.h"
#include "guimodel/point.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QToolButton;

class IModelControlReceiver;

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
  class GlobalMutex;


  class GraphEditor : public QWidget, 
		      public IGraphView,
		      public IControlConnectView,
		      public IModuleStatisticsReceiver,
		      public IModelStatusReceiver
  {
    Q_OBJECT
  private:

    std::map<int,NodeWidget*> nodes;
    
    typedef std::map<std::pair<int, int>,ConnectionWidget*> ConnectionMap;
    ConnectionMap connections;

    std::pair<int,int> selectedConnectionPair;
    
    QPainter mainPainter;

    QPoint oldLineFrom;
    QPoint oldLineTo;

    QPoint clickedPos;
    std::string currentModuleClassName;

    // moegliche aktionen der popup menues
    enum {NODEWIDGET_KILL,NODEWIDGET_TIMING,NODEWIDGET_PROPERTIES};
    enum {PLUGWIDGET_CONNECT_TO_CONTROL,PLUGWIDGET_REMOVE_CONTROL,
	  PLUGWIDGET_HIDE_INPUT, PLUGWIDGET_DISCONNECT};
    enum {CONNECTIONWIDGET_KILL};

    // der node bzw der input fuer den ein popup menue geoeffnet wurde:
    NodeWidget* currentNode;
    InputPlugWidget* currentInput;  

    GraphModel* m_controller;
    std::vector<QPixmap> nodePixmaps; 

    const InputPlugWidget* getInputPlugByPos(const QPoint& to) const;
    const OutputPlugWidget* getOutputPlugByPos(const QPoint& to) const;

    std::map<const InputPlugWidget*,bool> hasControl;

    std::map<const PlugWidget*,int> numConnections;

    const IModuleInfoBaseStation* infos;

    ControlValueDispatcher& dispatcher;

    IModelControlReceiver& model;


  public:
    GraphEditor(QWidget* parent, const char* name, WFlags fl,
		GraphModel& contr,
		const IModuleInfoBaseStation&,
		ControlValueDispatcher& dispatcher_,
		IModelControlReceiver&);

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

void beginLineDraw();
    void redrawLine(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput(const InputPlugWidget*,const QPoint& to);
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);
    void openPopup(InputPlugWidget*);
    void openPopup(NodeWidget*, const QPoint&);
    void openPopup(ConnectionWidget*,const QPoint&);

    void nodeWidgetMoved(NodeWidget*, const QPoint&);
    void nodeWidgetClicked(NodeWidget*);
    void nodeWidgetReleased(NodeWidget* n,const QPoint& pos);

    void nodePopupActivated(int);
    void inputPopupActivated(int);
    void connectionPopupActivated(int);

    void mouseOverInputPlug(const InputPlugWidget*);
    void mouseOverOutputPlug(const OutputPlugWidget*);

    void moduleClassSelected(const std::string&);

    signals:
    void createControl(const std::string& name,const std::string& type,
		       int nodeID,int inputIndex,const QPoint&);

    void deleteControl(int nodeID,int inputIndex);

    void statusText(const std::string&);
    void properties(const IPropertyDescription& pd);

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
    void removeOldLine();

    void decConnectionCount(PlugWidget* plug);
    void incConnectionCount(PlugWidget* plug);

private slots:
void displayTimings();
  };

} // end of namespace gui

#endif // GRAPHWIDGET_H
