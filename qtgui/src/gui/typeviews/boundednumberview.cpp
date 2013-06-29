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

#include <QtGui/qlayout.h>
#include <QtGui/QDoubleSpinBox>

#include "utils/structreader.h"

namespace gui
{
  class BoundedNumberView: public gui::TypeView
  {
    Q_OBJECT
  public:
    BoundedNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false)
    {
      utils::StructReader sr(params);
    
      double lowVal    = sr.getDoubleValue("lower_bound", 0);
      double highVal   = sr.getDoubleValue("higher_bound", 1);
      double stepSize  = sr.getDoubleValue("step_size", 0.1);
      int precision    = sr.getIntValue("precision", 3);
      std::string display_format = sr.getStringValue("display_format", 
                                                     "auto");
      std::string special_value_text = sr.getStringValue("special_text",
                                                         "");

      m_spin = new QDoubleSpinBox(this);

      m_spin->setRange(lowVal, highVal);
      m_spin->setDecimals(precision);
      m_spin->setSingleStep(stepSize);
      
      if (!special_value_text.empty())
        m_spin->setSpecialValueText(special_value_text.c_str());

      // TODO: display_format is ignored for now

      m_layout->addWidget(m_spin);
      m_spin->show();
		
      connect(m_spin, SIGNAL(valueChanged(double)),
              this, SLOT(spinboxChanged(double)));
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double value = 0;
      is >> value;
      
      if (fabs(value - m_spin->value()) >= 1 / pow(10, m_spin->decimals()))
        {
          m_setValueCalled = true;
          m_spin->setValue(value);
        }
    }

  private slots:
    void spinboxChanged(double newValue)
    {
      if (!m_setValueCalled)
        {
          std::ostringstream os;
          os << newValue;
          utils::Buffer
            newValue(reinterpret_cast<const unsigned char*>(os.str().c_str()),
                     os.str().length()+1);
		  
          emit valueChanged(newValue);
        }
      else
        {
          m_setValueCalled = false;
        }
    }

  private:
    QDoubleSpinBox* m_spin;
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
