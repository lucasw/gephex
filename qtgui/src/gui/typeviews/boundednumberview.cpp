#include "boundednumberview.h"

#include "utils/structreader.h"
#include <qlayout.h>
#include <qspinbox.h>

#include <qvalidator.h>
#include <sstream>

namespace gui
{
    static const int RESOLUTION = INT_MAX;
  class DoubleSpinBox : public QSpinBox
  {
  public:

    DoubleSpinBox(double lowVal, double highVal, double stepSize,
		  QWidget* parent)
      : QSpinBox(0, RESOLUTION, 1, parent),
	m_lowVal(lowVal), m_highVal(highVal),
	m_scale(RESOLUTION / (highVal - lowVal))
    {
      m_intStepSize = (stepSize * m_scale);
      //      std::cout << "Stepsize = " << m_intStepSize << std::endl;
      this->setLineStep((int) m_intStepSize);
      //      this->setSteps((int) m_intStepSize, (int) m_intStepSize);

      QValidator* validator = new QDoubleValidator(lowVal, highVal, 6, this);
      this->setValidator(validator);
    }

    QString mapValueToText( int value )
    {
      std::ostringstream os;
      double val = ((double) value / m_scale) + m_lowVal;
      os.precision(6);
      os << val;
      /*      std::cout << "Wert = " << value << "(" << val 
	      << "), Text = " << os.str() << std::endl;*/
      return QString(os.str().c_str());
    }

    int mapTextToValue( bool* /*ok*/ )
    {
      double value = m_scale * (text().toDouble() - m_lowVal);
      //      std::cout << "Text = " << text() << ", Wert = " << value << std::endl;
      return static_cast<int>(value);
    }

    double getDoubleValue() const {
      return text().toDouble();
    }

    void setDoubleValue(double newVal) {
      double value;

      if (newVal < m_lowVal)
	value = m_lowVal;
      else if (newVal > m_highVal)
	value = m_highVal;
      else
	value = newVal;

      this->setValue(static_cast<int>((value - m_lowVal) * m_scale));
    }

  private:
    double m_lowVal;
    double m_highVal;
    double m_intStepSize;
    double m_scale;
  };

  class BoundedNumberView: public gui::TypeView
  {
    Q_OBJECT
  public:
    BoundedNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false)
    {
      utils::StructReader sr(params);
      // wenn wertebereich definiert ist, übernehmen
    
      double lowVal    = sr.getDoubleValue("lower_bound", 0);
      double highVal   = sr.getDoubleValue("higher_bound", 1);
      double stepSize  = sr.getDoubleValue("step_size", 0.01);

      QHBoxLayout* l = new QHBoxLayout(this);
      m_spin = new DoubleSpinBox( lowVal, highVal, stepSize, this );
      m_spin->setMinimumSize(40, 33);
      //m_spin->setMaximumSize(60, 20);
      //m_spin->resize(40, 20);	
      m_spin->show();
      l->addWidget(m_spin);
		
      connect(m_spin, SIGNAL(valueChanged(int)),
		      this, SLOT(spinboxChanged(int)));

    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double value;
      is >> value;

      m_setValueCalled = true;
      m_spin->setDoubleValue(value);
    }

private slots:
    void spinboxChanged(int)
    {
      if (!m_setValueCalled)
	{
	  const QString& current = m_spin->text();
	  utils::Buffer
	    newValue(reinterpret_cast<const unsigned char*>(current.latin1()),
		     current.length()+1);

	  emit valueChanged(newValue);
	}
      else
	{
	  m_setValueCalled = false;
	}
    }

  private:
    DoubleSpinBox* m_spin;

    bool m_setValueCalled;
  };
 
	
  // constructor

  BoundedNumberViewConstructor::BoundedNumberViewConstructor()
    : TypeViewConstructor("Spin Box", "number_selector")
  {
  }
	

  TypeView*
  BoundedNumberViewConstructor::construct(QWidget* parent,
					  const ParamMap& params) const
  {
    return new BoundedNumberView(parent, params);
  }
}

#include "boundednumberview_moc.cpp"
