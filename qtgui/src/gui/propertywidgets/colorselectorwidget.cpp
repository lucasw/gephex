#include "colorselectorwidget.h"

#include "qlayout.h"
#include "qpushbutton.h"
#include "qcolordialog.h"
#include "qtooltip.h"

#include <sstream>

namespace gui
{

  PropertyColorSelectorWidget::PropertyColorSelectorWidget(QWidget* parent,
							   const char* name,
							   WFlags fl,
							   int nodeID,
							   int inputIndex,
							   int controlID,
							   const std::map<std::string,std::string>& params,
							   IModelControlReceiver& mo)
    :PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID,mo,params)
  {
		
    QHBoxLayout* l = new QHBoxLayout(this);
    select = new QPushButton("Select",this);
    select->setMinimumSize(40, 33);
    //select->setMaximumSize(60, 20);
    //select->resize(40, 20);	
    select->show();
    l->addWidget(select);
		
    connect(select, SIGNAL(clicked()), this, SLOT(colorSelectRequest()));
  }
	
  utils::Buffer PropertyColorSelectorWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),
			 current.length()+1);
  }
	
  void PropertyColorSelectorWidget::colorSelectRequest()
  {
    //TOD: default color
    QColor tmp = QColorDialog::getColor ( QColor(128, 128, 128), this, "ColorSelector") ;
		
    if (tmp.isValid())
      {
	std::ostringstream os("");
	double r,g,b;
	os.precision(3);
	r = (double) tmp.red()/255.;
	g = (double) tmp.green()/255.;
	b = (double) tmp.blue()/255.;
			
	os << r;
	os << " ";
	os << g;
	os << " ";
	os << b;
			
	current = os.str();
			
	setValue(getValue());
      }
  }

  PropertyColorSelectorWidget::~PropertyColorSelectorWidget()
  {
    //		std::cout << "MIST" << std::endl;
  }


  void PropertyColorSelectorWidget::controlValueChanged(int nodeID,int intputIndex,
							const utils::Buffer& newValue)
  {
    const char* newVal = reinterpret_cast<const char*>(newValue.getPtr());
    std::istringstream is(newVal);
    double r,g,b;
			
    is >> r >> g >> b;
    //      std::cout << "(" << r << "," << g << "," << b << ")" << std::endl;
			
    QColor newColor(r*255,g*255,b*255);
    select->setPalette(QPalette(newColor));
    QToolTip::add(this,newVal);
  }

  // constructor

  PropertyColorSelectorWidgetConstructor::PropertyColorSelectorWidgetConstructor():
    PropertyWidgetConstructor("typ_ColorType","color_selector",
			      "color_selector")
  {
  }
	

  PropertyWidget*
  PropertyColorSelectorWidgetConstructor::construct(QWidget* parent,
						    const std::string& name,
						    int controlID,int nodeID,
						    int inputIndex,
						    const std::map<std::string,std::string>& params,
						    IModelControlReceiver& mo)
  {
    return new PropertyColorSelectorWidget(parent,"color_selector",0,
					   nodeID,inputIndex,controlID,
					   params,mo);
  }

}
