/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "boundednumberview.h"

#include <sstream>
#include <cmath>

#include <qlayout.h>
#include <qspinbox.h>
#include <qvalidator.h>

#include "utils/structreader.h"

namespace gui
{
  static const int RESOLUTION = INT_MAX;
  class DoubleSpinBox : public QSpinBox
  {
  public:

    DoubleSpinBox(QWidget* parent, double lowVal, double highVal,
		          double stepSize, int precision,
				  const std::string& display_format,
				  const std::string& special_value_text)
      : QSpinBox(0, RESOLUTION, 1, parent),
	m_lowVal(lowVal), m_highVal(highVal),
	m_scale(RESOLUTION / (highVal - lowVal)),
	m_precision(precision)
    {
      m_intStepSize = (stepSize * m_scale);
      //      std::cout << "Stepsize = " << m_intStepSize << std::endl;
      this->setLineStep((int) m_intStepSize);
      //      this->setSteps((int) m_intStepSize, (int) m_intStepSize);

      QValidator* validator = new QDoubleValidator(lowVal, highVal,
		                                           m_precision, this);
      this->setValidator(validator);

	  m_os.precision(m_precision);
	  if (display_format == "fixed")
		  m_os.setf(std::ios::fixed, std::ios::floatfield);
	  else if (display_format == "scientific")
		  m_os.setf(std::ios::scientific, std::ios::floatfield);
	  // else don't set -> automatic mode

	  if (special_value_text != "")
		  this->setSpecialValueText(special_value_text.c_str());

	  // set some arbitrary value, otherwise the initial value
	  // will not be set correctly
	  setValue((int) (.27*RESOLUTION));	  
    }

    QString mapValueToText( int value )
    {   
      double val = ((double) value / m_scale) + m_lowVal;
	  m_os.str("");
      m_os << val;
	  m_os.flush();
      /*      std::cout << "Wert = " << value << "(" << val 
	      << "), Text = " << os.str() << std::endl;*/
      return QString(m_os.str().c_str());
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
		
		double scaled = (value - m_lowVal) * m_scale;
		this->setValue(static_cast<int>(floor(scaled+0.5)));
    }

  private:
    double m_lowVal;
    double m_highVal;
    double m_intStepSize;
    double m_scale;
	int    m_precision;
	std::ostringstream m_os;
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
	  int precision    = sr.getIntValue("precision", 6);
	  std::string display_format = sr.getStringValue("display_format", 
		                                             "auto");
	  std::string special_value_text = sr.getStringValue("special_text",
		                                                  "");

      QHBoxLayout* l = new QHBoxLayout(this);
      m_spin = new DoubleSpinBox(this, lowVal, highVal,
		                         stepSize, precision,
								 display_format,
								 special_value_text);

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
      double value = 0;
      is >> value;
      
	  if (fabs(value - m_spin->getDoubleValue()) > 0.0000001)
	  {
		m_setValueCalled = true;
		m_spin->setDoubleValue(value);
	  }
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
    : TypeViewConstructor("spin box", "number_selector")
  {
  }
	

  TypeView*
  BoundedNumberViewConstructor::construct(QWidget* parent,
					  const ParamMap& params) const
  {
    return new BoundedNumberView(parent, params);
  }
}

#include "boundednumberview_moc_cpp.cpp"
