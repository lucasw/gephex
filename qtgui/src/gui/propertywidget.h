#ifndef INCLUDED_PROPERTY_WIDGET_H
#define INCLUDED_PROPERTY_WIDGET_H

#include <string>
#include <map>

#include <qframe.h>

#include "interfaces/icontrolvaluereceiver.h"
#include "utils/buffer.h"

class IModelControlReceiver;

namespace gui
{

  class PropertyWidget : public QWidget,
			 public IControlValueReceiver
  {
    /*Q_OBJECT*/
  public:
    typedef std::map<std::string,std::string> ParamMap;
    PropertyWidget(QWidget* parent, const char* name, WFlags fl,               
		   int nodeID,int inIndex, int controlID,
		   IModelControlReceiver&,
		   const ParamMap& params);

    virtual ~PropertyWidget();
  
    virtual utils::Buffer getValue() const = 0;

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue) = 0;

    virtual void syncInputValuesStarted();
    virtual void syncInputValuesFinished();
  
    int getControlID() const;
    int getNodeID() const;
    int getInputIndex() const;

  protected:

    void setValue(const utils::Buffer& b);
  

  private:
    int m_controlID;
    int m_nodeID;
    int m_inputIndex;
    IModelControlReceiver& mcr;
  };

  class PropertyWidgetConstructor
  {
  public:
    typedef PropertyWidget::ParamMap ParamMap;

    PropertyWidgetConstructor(const std::string& type,const std::string& name,
			      const std::string& id);
    virtual ~PropertyWidgetConstructor();
    const std::string& getType();
    const std::string& getName();
    const std::string& getID();
    virtual PropertyWidget* construct(QWidget* parent, const std::string& name,
				      int controlID, int nodeID,
				      int inputIndex,
				      const ParamMap&,
				      IModelControlReceiver& mo)=0;
  private:
    const std::string m_type;
    const std::string m_name;
    const std::string m_id;

  };
 
}

#endif
