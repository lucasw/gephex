#include "numberselectorwidget.h"

#include "utils/structreader.h"
#include "qlayout.h"
#include "qspinbox.h"

#include <qmessagebox.h> //DEBUG

#include <sstream>

namespace gui
{

  NumberSelectorWidget::NumberSelectorWidget(QWidget* parent, const char* name,
					     WFlags fl,int nodeID,
					     int inputIndex, int controlID,
					     const ParamMap& params,
					     IModelControlReceiver& mo)
    :PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID,
		    mo, params),
     valueChanged(false)
  {
    utils::StructReader sr(params);
    // wenn wertebereich definiert ist, übernehmen
    
    lowVal = sr.getIntValue("lower_bound", 0);
    highVal = sr.getIntValue("higher_bound", 255);
    
    transformNumbers = !sr.getBoolValue("absolute", false);
		
    QHBoxLayout* l = new QHBoxLayout(this);
    spin = new QSpinBox( lowVal, highVal, 1, this);
    spin->setMinimumSize(40, 33);
    //spin->setMaximumSize(60, 20);
    //spin->resize(40, 20);	
    spin->show();
    l->addWidget(spin);
		
    connect(spin, SIGNAL(valueChanged(int)), this, SLOT(numberInputRequest(int)));
  }
	
  utils::Buffer NumberSelectorWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),
			 current.length()+1);
  }
	
  void NumberSelectorWidget::numberInputRequest(int newVal)
  {
    if (!valueChanged)
      {
	std::ostringstream os;			
	double raw;
	if (transformNumbers)
	  raw = ((double) (newVal - lowVal)
		 * (double) UINT_MAX) / (double) (highVal-lowVal);
	else
	  raw = newVal;

	os << (unsigned int)(raw);
	current = os.str();
			
	setValue(getValue());
      }
    else
      {
	valueChanged = false;
      }
  }

  void NumberSelectorWidget::controlValueChanged(int nodeID,int intputIndex,
						 const utils::Buffer& newValue)
  {
    //QMessageBox::information(0, "NumberSelectorWidget","controlValueChanged()");
    valueChanged = true;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    unsigned int raw;
    is >> raw;
			

    double value;
	
    if (transformNumbers)
      value = ((double) raw * (double) (highVal-lowVal))
	/ (double) UINT_MAX + (double) lowVal;
    else
      value = raw;
			
    spin->setValue((unsigned int) value);
  }

  // constructor

  PropertyNumberSelectorWidgetConstructor::PropertyNumberSelectorWidgetConstructor():
    PropertyWidgetConstructor("typ_NumberType","number_selector",
			      "number_selector")
  {
  }
	

  PropertyWidget* PropertyNumberSelectorWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID, int nodeID, int inputIndex, const ParamMap& params ,IModelControlReceiver& mo)
  {
    return new NumberSelectorWidget(parent,"number_selector",0,nodeID,
				    inputIndex,controlID,params,mo);
  }

}
