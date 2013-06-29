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
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "radionumberview.h"

#include <sstream>
#include <cmath>

#include <QtGui/qlayout.h>
#include <QtGui/qradiobutton.h>

#include "utils/structreader.h"


/**
 * RadioButton: mögliche true/false -Werte können mittels 
 * true_value= bzw. false_value= aus dem Modul übergeben werden. 
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
        m_isChecked(0)
    {
      utils::StructReader sr(params);
      
      // wenn wertebereich definiert ist, übernehmen
      m_trueVal = sr.getDoubleValue("true_value", 1);
      m_falseVal = sr.getDoubleValue("false_value", 0);
    	
      m_radio = new QRadioButton(this);
      m_layout->addWidget(m_radio);
		
      connect(m_radio, SIGNAL(toggled(bool)),
              this, SLOT(radiobuttonChanged(bool)));

      m_radio->show();
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw;
      is >> raw;
		
      bool checked = fabs(raw - m_trueVal) < fabs(raw - m_falseVal);
      if (checked != m_isChecked)
        {          
          m_setCheckedCalled = true;
          m_isChecked = checked;
          if(checked)
            {
              m_radio->setChecked(true);
            }
          else
            {		
              m_radio->setChecked(false);
            }
        }
    }
		
  private slots:
    void radiobuttonChanged(bool)
    {
      if (!m_setCheckedCalled)
        {
          std::ostringstream os;

          if(!m_isChecked)
            os << m_trueVal;
          else
            os << m_falseVal;

          m_isChecked = !m_isChecked;

          os.flush();          

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

#include "radionumberview_moc_cpp.cpp"

