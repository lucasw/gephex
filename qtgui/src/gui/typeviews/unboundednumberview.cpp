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

#include "unboundednumberview.h"

#include <sstream>
#include <cmath>

#include <QtGui/qvalidator.h>
#include <QtGui/qlineedit.h>
#include <QtGui/QHBoxLayout>

#include <utils/structreader.h>
#include <utils/buffer.h>

namespace gui
{

  class UnboundedNumberView: public gui::TypeView
  {
    Q_OBJECT
  public:
    UnboundedNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_value(-1.0)
    {
      utils::StructReader sr(params);
      m_lineEdit = new QLineEdit(this);

      m_layout->addWidget(m_lineEdit);

      int precision = sr.getIntValue("precision", 6);
      std::string display_format = sr.getStringValue("display_format",
                                                     "auto");

      m_lineEdit->setValidator(new QDoubleValidator(this));

      m_os.precision(precision);
      if (display_format == "fixed")
        m_os.setf(std::ios::fixed, std::ios::floatfield);
      else if (display_format == "scientific")
        m_os.setf(std::ios::scientific, std::ios::floatfield);
      // else don't set -> automatic mode

      connect(m_lineEdit, SIGNAL(returnPressed()),
	      this, SLOT(lineeditChanged()));
    }
		
    virtual ~UnboundedNumberView() {}
		
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::string doof = reinterpret_cast<const char*>(newValue.getPtr());
      std::istringstream is(doof);
      double value = 0;
      is >> value;

	  if (fabs(value - m_value) > 0.00001)
	  {
		  m_value = value;
		  m_os.str("");		  
		  m_os << value;
		  
		  m_lineEdit->setText(m_os.str().c_str());
	  }
    }

public slots:
    void lineeditChanged()
    {
      QByteArray raw = m_lineEdit->text().toUtf8();
      const char* text = raw.constData();

      //      std::cout << "Lineedit text = '" << text << "'" << std::endl;
      utils::Buffer 
	b = utils::Buffer(reinterpret_cast<const unsigned char*>(text),
			  strlen(text)+1);

      emit valueChanged(b);
    }
		
  private:
    QLineEdit* m_lineEdit;
    double m_value;
    std::ostringstream m_os;
  };

  // constructor

  UnboundedNumberViewConstructor::UnboundedNumberViewConstructor()
    : TypeViewConstructor("number input", "unboundednumber_selector")
  {
  }

  TypeView* UnboundedNumberViewConstructor::construct(QWidget* parent,
						      const ParamMap& params)
    const
  {
    return new UnboundedNumberView(parent, params);
  }
}

#include "unboundednumberview_moc_cpp.cpp"
