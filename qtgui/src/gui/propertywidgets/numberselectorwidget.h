#ifndef NUMBERSELECTORWIDGET_H
#define NUMBERSELECTORWIDGET_H

#include <map>
#include "gui/propertywidget.h"
class QSpinBox;

namespace gui
{
  class NumberSelectorWidget: public gui::PropertyWidget
  {
    Q_OBJECT
			
  public:
    NumberSelectorWidget(QWidget* parent, const char* name, WFlags fl,
			 int nodeID, int inIndex, int controlID,
			 const ParamMap& params,
			 IModelControlReceiver& mo);
		
    virtual utils::Buffer getValue() const;
		
    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);


  private:
    QSpinBox* spin;
    std::string  current;
    int lowVal;
    int highVal;
    bool valueChanged;
    bool transformNumbers;

private slots:
void numberInputRequest(int);
  };
	
  class PropertyNumberSelectorWidgetConstructor
    : public PropertyWidgetConstructor
  {
  public:
    PropertyNumberSelectorWidgetConstructor();
    virtual PropertyWidget* construct(QWidget* parent,
				      const std::string& name,
				      int controlID,
				      int nodeID, int inputIndex,
				      const ParamMap&,
				      IModelControlReceiver& mo);
  };


}

#endif
