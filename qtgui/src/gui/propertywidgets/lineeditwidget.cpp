#include "lineeditwidget.h"

#include "utils/structreader.h"
#include "utils/buffer.h"

#include "qlineedit.h"
#include "qtooltip.h"


namespace gui
{

  PropertyLineEditWidget::PropertyLineEditWidget(QWidget* parent,
						 const char* name, WFlags fl,
						 int nodeID, int inIndex,
						 int controlID,
						 const std::map<std::string,std::string>& params,
						 IModelControlReceiver& mo)
    : PropertyWidget(parent,name,fl,nodeID,inIndex,controlID,mo,params),
      valueChanged(false)
  {
    utils::StructReader sr(params);
    std::string defaultValue = "";
    try
      {
	defaultValue = sr.getStringValue("default_value");
      }
    catch (...)
      {
      }
		
    lineEdit = new QLineEdit(defaultValue.c_str(),this,0);
    connect(lineEdit, SIGNAL(returnPressed()),
	    this, SLOT(textChanged_()));
  }
	
  utils::Buffer PropertyLineEditWidget::getValue() const
  {
    std::string text = lineEdit->text().latin1();
    return utils::Buffer(reinterpret_cast<const unsigned char*>(text.c_str()),
			 text.length()+1);
  }
	
  void PropertyLineEditWidget::textChanged_()
  {
    if (!valueChanged)
      {
	setValue(getValue());
      }
    else
      valueChanged = false;
  }

  void PropertyLineEditWidget::controlValueChanged(int nodeID,int intputIndex,
						   const utils::Buffer& newValue)
  {
    valueChanged = true;

    const char* doof = reinterpret_cast<const char*>(newValue.getPtr());
    lineEdit->setText(doof);
    QToolTip::add(this,doof);
  }

  // constructor

  PropertyLineEditWidgetConstructor::PropertyLineEditWidgetConstructor():
    PropertyWidgetConstructor("typ_StringType","line_edit","line_edit")
  {
  }
	

  PropertyWidget* PropertyLineEditWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID,
							       int nodeID, int inputIndex,const std::map<std::string,std::string>& params ,IModelControlReceiver& mo)
  {
    return new PropertyLineEditWidget(parent,"line_edit",0,nodeID,inputIndex,controlID,params,mo);
  }



}
