#include "radiobuttonwidget.h"

#include "utils/structreader.h"
#include "qlayout.h"
#include "qradiobutton.h"

#include <sstream>

/**
* RadioButton: mögliceh true/false -Werte können mittels 
* true_value= bzw. false_value= aus dem Modul übergeben werden. 
*/
namespace gui
{

  RadioButtonWidget::RadioButtonWidget(QWidget* parent, const char* name,
				       WFlags fl,int nodeID,
				       int inputIndex, int controlID,
				       const std::map<std::string,std::string>& params,
				       IModelControlReceiver& mo)
    :PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID, mo,params),
     valueChanged(false)
  {
    utils::StructReader sr(params);
    oldValue = 0;
    // wenn wertebereich definiert ist, übernehmen
    
    trueVal = sr.getIntValue("true_value", 0);
    falseVal = sr.getIntValue("false_value", UINT_MAX);
    	
    QHBoxLayout* l = new QHBoxLayout(this);
    radio = new QRadioButton(this);
    radio->setMinimumSize(40, 33);

    radio->show();
    l->addWidget(radio);
		
    connect(radio, SIGNAL(stateChanged(int)), this, SLOT(radioButtonRequest(int)));
  }
	
  utils::Buffer RadioButtonWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),
			 current.length()+1);
  }
	
  void RadioButtonWidget::radioButtonRequest(int)
  {
    if (!valueChanged)
      {
	std::ostringstream os;			
			
	if(!oldValue)
	  {
	    os << trueVal;
	    oldValue = 1;
	  }
	else
	  {
	    os << falseVal;
	    oldValue = 0;
	  }

	current = os.str();
	setValue(getValue());				
      }
    else
      {
	valueChanged = false;
      }
  }

  void RadioButtonWidget::controlValueChanged(int nodeID,int intputIndex,
					      const utils::Buffer& newValue)
  {
    valueChanged = true;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    unsigned int raw;
    is >> raw;
		
    if(raw == trueVal)
      radio->setChecked(true);
    else
      radio->setChecked(false);
  }


  // constructor

  PropertyRadioButtonWidgetConstructor::PropertyRadioButtonWidgetConstructor():
    PropertyWidgetConstructor("typ_NumberType","radio_button",
			      "radio_button")
  {
  }
	

  PropertyWidget*
  PropertyRadioButtonWidgetConstructor::construct(QWidget* parent,
						  const std::string& name,
						  int controlID,int nodeID,
						  int inputIndex,
						  const std::map<std::string,std::string>& params,
						  IModelControlReceiver& mo)
  {
    return new RadioButtonWidget(parent,"radio_button",0,nodeID,inputIndex,
				 controlID,params,mo);
  }

}
