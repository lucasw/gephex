#ifndef RADIOBUTTONWIDGET_H
#define RADIOBUTTONWIDGET_H

#include <map>
#include "gui/propertywidget.h"
class QRadioButton;

namespace gui
{


  class RadioButtonWidget: public gui::PropertyWidget
  {
    Q_OBJECT
			
  public:
    RadioButtonWidget(QWidget* parent, const char* name, WFlags fl,
		      int nodeID, int inIndex, int controlID,
		      const std::map<std::string,std::string>& params,
		      IModelControlReceiver& mo);
		
    virtual utils::Buffer getValue() const;
		
    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);


  private:
    QRadioButton* radio;
    std::string  current;
    unsigned int oldValue;
    unsigned int falseVal;
    unsigned int trueVal;
    bool valueChanged;
		
private slots:
void radioButtonRequest(int);
  };


class PropertyRadioButtonWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyRadioButtonWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};

}

#endif
