#ifndef _INCLUDED_CONTROL_EDITOR_H_
#define _INCLUDED_CONTROL_EDITOR_H_

#include <list>
#include <map>
#include <string>

#include <qwidget.h>

#include "guimodel/icontrolview.h"
#include "guimodel/point.h"

namespace utils {
  class Buffer;
}

class IModelControlReceiver;

namespace gui
{

  class ControlModel;
  class ControlWidgetFactory;
  class ControlWidget;
  class ControlValueDispatcher;

  class ControlEditor: public QWidget, 
		       public IControlView
  {
    Q_OBJECT
  public:
    enum {CONTROLELEMENTWIDGET_KILL};

    ControlEditor(QWidget* parent, const char* name, WFlags fl,
		  ControlModel& cModel, IModelControlReceiver& model,
		  ControlValueDispatcher& disp);

    virtual ~ControlEditor();

    virtual void controlAdded(int controlID, const std::string& name,
			      int nodeID,int inputIndex, 
			      const std::string& widgetType);

    virtual void controlMoved(int controlID, const Point& p);
    virtual void controlDeleted(int controlID);

    virtual void controlRenamed(int controlID, const std::string& name);

public slots:
void controlChanged(int nodeID,int inputIndex, const utils::Buffer&);

    void selectWidgetType(const std::string& name, const std::string& type,
			  int nodeID,int inputIndex,
			  const QPoint&);

    void deleteControl(int nodeID,int inputIndex);

    void controlWidgetMoved(ControlWidget*, const QPoint&);
	
    void controlWidgetReleased(ControlWidget* n,const QPoint& pos);

    void openPopup(ControlWidget*, const QPoint&);

protected slots:
void widgetTypeSelected(int);

    void controlPopupActivated(int action);

  protected:
    virtual void mousePressEvent(QMouseEvent*);

  private:
    ControlModel* m_controller;
    IModelControlReceiver* m_model;
    ControlWidgetFactory* m_factory;	
	
    std::map<int,ControlWidget*> widgets;

    Point clickedPos;
    int currentNodeID;
    int currentInputIndex;
    std::string currentName;
    std::string currentWidgetType;

    std::map<int,std::string> id2Identifier;
    ControlWidget* currentControl;

    ControlValueDispatcher* m_controlValueDispatcher;
  };

} // end of namespace gui

#endif
