#include "radionumberview.h"

#include <sstream>
#include <cmath>

#include <qlayout.h>
#include <qradiobutton.h>

#include "utils/structreader.h"


/**
* RadioButton: m�gliceh true/false -Werte k�nnen mittels 
* true_value= bzw. false_value= aus dem Modul �bergeben werden. 
*/
namespace gui
{


  class RadioNumberView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    RadioNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params),
        m_setCheckedCalled(false),
        m_isChecked(0), m_value(-1)
    {
      utils::StructReader sr(params);
      
      // wenn wertebereich definiert ist, �bernehmen
      m_trueVal = sr.getDoubleValue("true_value", 1);
      m_falseVal = sr.getDoubleValue("false_value", 0);
    	
      QHBoxLayout* l = new QHBoxLayout(this);
      m_radio = new QRadioButton(this);
      l->addWidget(m_radio);

      //m_radio->setMinimumSize(40, 33);
      this->resize(m_radio->sizeHint());
		
      connect(m_radio, SIGNAL(stateChanged(int)),
              this, SLOT(radiobuttonChanged(int)));

      m_radio->show();
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw;
      is >> raw;
		
      if (fabs(raw - m_value) > 0.0001)
        {
          m_value = raw;
          m_setCheckedCalled = true;
          if(fabs(raw - m_falseVal) < fabs(raw - m_trueVal))
            m_radio->setChecked(false);
          else
            m_radio->setChecked(true);
        }
    }
		
private slots:
void radiobuttonChanged(int)
    {
      if (!m_setCheckedCalled)
        {
          std::ostringstream os;

          if(!m_isChecked)
            os << m_trueVal;
          else
            os << m_falseVal;

          os.flush();

          m_isChecked = !m_isChecked;

          utils::Buffer
            b (reinterpret_cast<const unsigned char*>(os.str().c_str()),
               os.str().length()+1);
          emit valueChanged(b);
        }
      else
        {
          m_setCheckedCalled = false;
        }
    }

  private:
    QRadioButton* m_radio;
    bool m_setCheckedCalled;
    bool m_isChecked;
    double m_value;
    double m_falseVal;
    double m_trueVal;

  };

  // constructor

  RadioNumberViewConstructor::RadioNumberViewConstructor():
    TypeViewConstructor("radio button", "radio_button")
  {
  }
	

  TypeView* RadioNumberViewConstructor::construct(QWidget* parent,
						  const ParamMap& params)
    const
  {
    return new RadioNumberView(parent, params);
  }

}

#include "radionumberview_moc.cpp"

