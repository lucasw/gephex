#include "dialnumberview.h"

#include <sstream>
#include <cmath>

#include <qdial.h>
#include <qlayout.h>
//#include <qmessagebox.h>

#include "utils/buffer.h"
#include "utils/structreader.h"

namespace gui
{

  static const int RESOLUTION = 255;
  class DialNumberView : public gui::TypeView
  {
    Q_OBJECT
    
  public:
    DialNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false), m_value(0)
    {
      QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,0);

      utils::StructReader sr(params);
      m_lowVal    = sr.getDoubleValue("lower_bound", 0);
      m_highVal   = sr.getDoubleValue("higher_bound", 1);
      
      m_dial = new QDial(0, RESOLUTION, 1, 0, this, "dial");
	  layout->addWidget(m_dial);

	  //this->resize(m_dial->sizeHint());
	  this->resize(50,50);

      connect(m_dial, SIGNAL(valueChanged(int)), this, SLOT(dialChanged(int)));
    }

    virtual void valueChange(const utils::Buffer& newValue) {

      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw = 0;
      is >> raw;
      double d = (raw - m_lowVal) / (m_highVal - m_lowVal) * RESOLUTION;

      if (d < 0)
	d = 0;
      else if (d > RESOLUTION)
	d = RESOLUTION;

      if (fabs(d - m_value) > 0.00001)
	  {
		m_value = d;
		m_setValueCalled = true;
		m_dial->setValue((int) d);
	  }
    }

private slots:
    void dialChanged(int newVal)
    {
	  if (!m_setValueCalled)
	  {
		  double i = newVal / (double) RESOLUTION;
		  i = i * (m_highVal - m_lowVal) + m_lowVal;
		  
		  std::ostringstream s;
		  s << i;
		  std::string data = s.str();
		  const unsigned char*
			  udata = reinterpret_cast<const unsigned char*>(data.c_str());
		  emit valueChanged(utils::Buffer(udata, data.length()+1));
	  }
	  else
	  {
		  m_setValueCalled = false;
	  }
    }

  private:
    QDial* m_dial;
	bool m_setValueCalled;
	double m_value;
    double m_lowVal;
    double m_highVal;
  };




  DialNumberViewConstructor::DialNumberViewConstructor()
    : TypeViewConstructor("dial", "dial") {}

  TypeView* DialNumberViewConstructor::construct(QWidget* parent,
					   const ParamMap& params) const
  {
    return new DialNumberView(parent, params);
  }

}

#include "dialnumberview_moc.cpp"
