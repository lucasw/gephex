#ifndef INCLUDED_CONTROL_WIDGET_H
#define INCLUDED_CONTROL_WIDGET_H

#include <string>
#include <map>

#include <qframe.h>

#include "interfaces/icontrolvaluereceiver.h"

namespace utils {
  class Buffer;
}	

namespace gui
{
  class TypeViewConstructor;
  class TypeView;

  class ControlWidget : public QFrame, 
			public IControlValueReceiver
  {

    Q_OBJECT
  public:
    typedef std::map<std::string, std::string> ParamMap;

    ControlWidget(QWidget* parent, const std::string& name, int controlID,
		  int nodeID, int inputIndex,
		  const ParamMap& params,
		  const TypeViewConstructor* con);

    virtual ~ControlWidget();

    std::string name() const { return m_name; }
    int controlID() const { return m_controlID; }
    int nodeID() const { return m_nodeID; }
    int inputIndex() const { return m_inputIndex; }

    QWidget* getLabel();

    void setName(const std::string& newName);	

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);

    virtual void syncInputValuesStarted();
    virtual void syncInputValuesFinished();

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent* e);

protected slots:
void changeValue(const utils::Buffer&);
	

    signals:
void valueChanged(int,int,const utils::Buffer&);
    void moved(ControlWidget*, const QPoint&);
    void released(ControlWidget*, const QPoint&);

    void beenRightClicked(ControlWidget*, const QPoint& );


  private:
    std::string m_name;
    int m_controlID;
    int m_nodeID;
    int m_inputIndex;
    bool dragMode;
    QPoint clickedPos;
    QWidget* m_label;
    TypeView* m_view;
  };
}
#endif
