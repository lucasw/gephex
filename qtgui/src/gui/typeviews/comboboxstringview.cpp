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

#include "comboboxstringview.h"

#include <iostream>

#include <QtGui/qcombobox.h>
#include <QtGui/qlayout.h>

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"

namespace gui
{

  class ComboboxStringView : public gui::TypeView
  {
    Q_OBJECT		
  public:
    ComboboxStringView(QWidget* parent,
		       const ParamMap& params)
      : TypeView(parent, params)
    {
      
      m_box = new QComboBox(this);
      m_layout->addWidget(m_box);

      try
        {
          utils::StructReader sr(params);
          std::string values = sr.getStringValue("values");
			
          utils::StringTokenizer tok(values);
          int index = 0;
          for (std::string token = tok.next(",");
               token != ""; token = tok.next(","), ++index)
            {
              m_box->insertItem(index, token.c_str());
              m_values[token] = index;
            }
        }
      catch(...)
	{
	}

	
      connect(m_box, SIGNAL(activated(const QString&)),
	      this,SLOT(comboboxChanged(const QString&)));
    }

    void valueChange(const utils::Buffer& newValue)
    {
      int len = newValue.getLen();
      const char* raw;
      if (len <= 0)
        {
          raw = "";
          len = 1;
        }
      else
        {
          raw = reinterpret_cast<const char*>(newValue.getPtr());
        }

      if (raw[len-1] != 0)
        {
          std::cout << "ignoring string with missing termination\n";
          return;
        }

      std::string str ( raw, len );
      ValueMap::const_iterator it = m_values.find(str.c_str());
			
      if (it == m_values.end())
	{
	  //bad idea! don't throw!!
          //	throw std::runtime_error("Invalid combobox value: '" + str + "'");
          fprintf(stderr, "Ignoring invalid value '%s' at "
                  "ComboboxStringView::valueChange\n", str.c_str());
	}
      else
        {
          m_box->setCurrentIndex(it->second);
        }
    }


  public slots:
    void comboboxChanged(const QString& s)
    {
      QByteArray raw = s.toUtf8();
      const unsigned char* str 
	= reinterpret_cast<const unsigned char*>(raw.constData());

      emit valueChanged(utils::Buffer(str,s.length()+1));
    }

  private:
    typedef std::map<std::string, int> ValueMap;
    ValueMap m_values;
    QComboBox* m_box;
  };

  // constructor

  ComboboxStringViewConstructor::ComboboxStringViewConstructor()
    : TypeViewConstructor("combo box", "combo_box")
  {
  }

  TypeView*
  ComboboxStringViewConstructor::construct(QWidget* parent,
					   const ParamMap& params) const
  {
    return new ComboboxStringView(parent, params);
  }

}

#include "comboboxstringview_moc_cpp.cpp"
