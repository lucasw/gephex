#include "dialwidget.h"

#include "qdial.h"
#include "qlayout.h"
#include <sstream>

#include "utils/buffer.h"

namespace gui
{
  DialWidget::DialWidget(QWidget* parent, const std::string& name,  int controlID,
			 int nodeID,int inIndex):
    ControlWidget(parent, name, controlID, nodeID, inIndex), itWasMe(false)
  {
    this->resize(50, 50);

    //get yourself some cool style
	
    //TODO: caution -> min- and maxValue are chosen ... whatever...
    dial = new QDial(0, 255, 1, 128, this, "whatever");
	
    QVBoxLayout* layout = new QVBoxLayout(this,QBoxLayout::TopToBottom,7);
    layout->addWidget(dial,0,Qt::AlignCenter);

    connect(dial,SIGNAL(valueChanged(int)),this,SLOT(intValueChanged(int)));
  }

  void DialWidget::controlValueChanged(int nodeID,int intputIndex,
				       const utils::Buffer& newValue)
  {
    itWasMe = true;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    unsigned int raw;
    is >> raw;
    double d = ((double) raw / (double) UINT_MAX) * 255.;
    dial->setValue((int) d);		
  }


  void DialWidget::intValueChanged(int newVal)
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
	itWasMe = false;
      }
  }

  // constructor klass

  DialWidgetConstructor::DialWidgetConstructor():
    ControlWidgetConstructor("typ_NumberType","Drehknopf","dial")
  {
  }
		
  ControlWidget* DialWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID,
						  int nodeID, int inputIndex)
  {
    return new DialWidget(parent,name,controlID,nodeID,inputIndex);
  }


}
