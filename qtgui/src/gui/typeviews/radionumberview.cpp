#include "radionumberview.h"

#include <sstream>
#include <cmath>

#include <qlayout.h>
#include <qradiobutton.h>

#include "utils/structreader.h"


/**
* RadioButton: mögliceh true/false -Werte können mittels 
* true_value= bzw. false_value= aus dem Modul übergeben werden. 
*/
namespace gui
{


  class RadioNumberView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    RadioNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params)
    {
      utils::StructReader sr(params);
      m_oldValue = 0;
      // wenn wertebereich definiert ist, übernehmen
    
      m_trueVal = sr.getDoubleValue("true_value", 1);
      m_falseVal = sr.getDoubleValue("false_value", 0);
    	
      QHBoxLayout* l = new QHBoxLayout(this);
      m_radio = new QRadioButton(this);
      m_radio->setMinimumSize(40, 33);

      m_radio->show();
      l->addWidget(m_radio);
		
    connect(m_radio, SIGNAL(stateChanged(int)),
	    this, SLOT(radiobuttonChanged(int)));
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw;
      is >> raw;
		
      if(fabs(raw - m_falseVal) < 0.0001)
	m_radio->setChecked(false);
      else
	m_radio->setChecked(true);
    }
		
private slots:
    void radiobuttonChanged(int)
    {
      std::ostringstream os;			
			
      if(!m_oldValue)
	os << m_trueVal;
      else
	os << m_falseVal;

      m_oldValue = !m_oldValue;

      utils::Buffer
	b (reinterpret_cast<const unsigned char*>(os.str().c_str()),
	   os.str().length()+1);
      emit valueChanged(b);
    }

  private:
    QRadioButton* m_radio;
    bool m_oldValue;
    double m_falseVal;
    double m_trueVal;

  };

  // constructor

  RadioNumberViewConstructor::RadioNumberViewConstructor():
    TypeViewConstructor("Radio Button", "radio_button")
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

