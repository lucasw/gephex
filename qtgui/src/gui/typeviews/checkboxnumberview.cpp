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

#include "checkboxnumberview.h"

#include <sstream>
#include <cmath>
#include <vector>

#include <QtGui/qlayout.h>
#include <QtGui/QButtonGroup>
#include <QtGui/qcheckbox.h>
#include <QtGui/QGroupBox>
//#include <QtGui/qmessagebox.h>

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"


/**
 *
 * CheckBox
 *
 */
namespace gui
{


  class CheckBoxNumberView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    CheckBoxNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_value(0), m_num_buttons(0)
    {
      utils::StructReader sr(params);	  

      QGroupBox* grp = new QGroupBox(this);
      
      m_group = new QButtonGroup(grp);
      m_group->setExclusive(false);

      QVBoxLayout* buttonLayout = new QVBoxLayout(grp);

      // parameter aus params angucken
      try
        {
          std::string values = sr.getStringValue("values");
		  
          utils::StringTokenizer tok(values);
          for (std::string token = tok.next(",");
               token != ""; token = tok.next(","), ++m_num_buttons)
            {
              QCheckBox* cb = new QCheckBox(token.c_str(), grp);
              buttonLayout->addWidget(cb);
              QFont f = cb->font();
              f.setPointSize(8);
              cb->setFont(f);
              m_group->addButton(cb, m_num_buttons);
            }
        }
      catch(...)
        {
        }
	
      /*
      QSize min  = grp->minimumSize();
      QSize max  = grp->maximumSize();
      QSize pref = grp->sizeHint();
      std::ostringstream os;
      os << "width     = " << grp->width() << "\t height     = " << grp->height() << "\n";
      os << "minWidth  = " << min.width()      << "\t minHeight  = " << min.height() << "\n";
      os << "maxWidth  = " << max.width()      << "\t maxHeight  = " << max.height() << "\n";
      os << "prefWidth = " << pref.width()     << "\t prefHeight = " << pref.height() << "\n";
      QMessageBox::information( 0, "Info", os.str().c_str() );*/
      
      m_layout->addWidget(grp);
	  
      connect(m_group, SIGNAL(buttonClicked(int)),
              this, SLOT(boxToggled(int)));
	  
      grp->show();
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw;
      is >> raw;
	
      int new_value = static_cast<int>(floor(raw+0.5));

      if (m_value != new_value)
        {
          m_value = new_value;
		  
          for (int i = 0; i < m_num_buttons; ++i)
            {
              QCheckBox* cb = dynamic_cast<QCheckBox*>(m_group->button(i));
              if (m_value & (1 << i))		
                cb->setChecked(true);      
              else
                cb->setChecked(false);
            }
        }
    }
		
  private slots:
    void boxToggled(int index)
    {
      std::ostringstream os;			
      QCheckBox* cb = dynamic_cast<QCheckBox*>(m_group->button(index));
      if (cb->isChecked())
        {
          m_value |= (1 << index);
        }
      else
        {
          m_value &= ~(1 << index);
        }
      
      os << m_value;

      utils::Buffer 
        b(reinterpret_cast<const unsigned char*>(os.str().c_str()),
          os.str().length()+1);
      emit valueChanged(b);
    }

  private:
    QButtonGroup* m_group;
    int m_value;
    int m_num_buttons;
  };

  // constructor

  CheckBoxNumberViewConstructor::CheckBoxNumberViewConstructor():
    TypeViewConstructor("check box", "check_box")
  {
  }
	

  TypeView* CheckBoxNumberViewConstructor::construct(QWidget* parent,
                                                     const ParamMap& params)
    const
  {
    return new CheckBoxNumberView(parent, params);
  }

}

#include "checkboxnumberview_moc_cpp.cpp"

