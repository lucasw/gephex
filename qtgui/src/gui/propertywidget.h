#ifndef INCLUDED_PROPERTY_WIDGET_H
#define INCLUDED_PROPERTY_WIDGET_H

#include <string>
#include <map>

//#include <qframe.h>
#include <qwidget.h>

#include "interfaces/icontrolvaluereceiver.h"
#include "utils/buffer.h"

class IModelControlReceiver;

namespace gui
{
  class TypeView;
  class TypeViewConstructor;

  class PropertyWidget : public QWidget,
			 public IControlValueReceiver
  {
    Q_OBJECT
  public:
    typedef std::map<std::string,std::string> ParamMap;
    PropertyWidget(QWidget* parent, const char* name, WFlags fl,               
		   int nodeID,int inIndex, int controlID,
		   IModelControlReceiver&,
		   const ParamMap& params,
		   const TypeViewConstructor& con);

    virtual ~PropertyWidget();
  
    //    virtual utils::Buffer getValue() const = 0;

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);

    virtual void syncInputValuesStarted();
    virtual void syncInputValuesFinished();
  
    int getControlID() const;
    int getNodeID() const;
    int getInputIndex() const;

  protected:

    void setValue(const utils::Buffer& b);
  
    private slots:
      void changeValue(const utils::Buffer& b);

  private:
    int m_controlID;
    int m_nodeID;
    int m_inputIndex;
    IModelControlReceiver& mcr;
    TypeView* m_view;
  };
 
}

#endif
