#include "sliderwidget.h"

#include "qslider.h"
#include "qlayout.h"
#include "qmessagebox.h"

#include <sstream>

#include "utils/buffer.h"

namespace gui
{
  void SliderWidget::controlValueChanged(int nodeID,int intputIndex,
					 const utils::Buffer& newValue)
  {
    itWasMe = true;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    unsigned int raw;
    is >> raw;
    double d = ((double) raw / (double) UINT_MAX) * 255.;
    slider->setValue((int) d);
  }

  SliderWidget::SliderWidget(QWidget* parent, Qt::Orientation orient,
			     const std::string& name, int controlID,
			     int nodeID,int inIndex):
    ControlWidget(parent, name, controlID, nodeID, inIndex), itWasMe(false)
  {
    if (orient == QSlider::Vertical)
      {
	this->resize(32, 100);
      }
    else
      {
	this->resize(100,32);
      }

    //get yourself some cool style
	
    //TODO: caution -> min- and maxValue are chosen ... whatever...
    slider = new QSlider(0, 255, 1, 128, orient, this, "whatever");
	
    QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,4);
    layout->addWidget(slider);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(intValueChanged(int)));	
  }

  void SliderWidget::intValueChanged(int newVal)
  {
    if (!itWasMe)
      {	
	unsigned int i = (unsigned int) ((double) (newVal / 255.) * UINT_MAX);
	std::ostringstream s;
	s << i;
	std::string data = s.str();		
	valueChanged(utils::Buffer(reinterpret_cast<const unsigned char*>(data.c_str()),
				   data.length()+1));
      }
    else
      {
	//QMessageBox::information(0, "It was me!", "Yes, thats true!!!!");
	itWasMe = false;
      }
  }

  // constructor klass H

  HSliderWidgetConstructor::HSliderWidgetConstructor():
    ControlWidgetConstructor("typ_NumberType","Horizontaler Slider","hslider")
  {
  }
		
  ControlWidget* HSliderWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID,
						     int nodeID, int inputIndex)
  {
    return new SliderWidget(parent,QSlider::Horizontal,name,controlID,nodeID,inputIndex);
  }

  // constructor klass  V

  VSliderWidgetConstructor::VSliderWidgetConstructor():
    ControlWidgetConstructor("typ_NumberType","Vertikaler Slider","vslider")
  {
  }
		
  ControlWidget* VSliderWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID,
						     int nodeID, int inputIndex)
  {
    return new SliderWidget(parent,QSlider::Vertical,name,controlID,nodeID,inputIndex);
  }

}
