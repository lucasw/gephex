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

#include "colorview.h"

#include <sstream>

#include <qlayout.h>
#include <qpushbutton.h>
#include <qcolordialog.h>
#include <qtooltip.h>

namespace gui
{

  class ColorView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    ColorView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_current("")
    {
      QHBoxLayout* l = new QHBoxLayout(this);
      m_select = new QPushButton("Select",this);
      m_select->setMinimumSize(40, 33);
      //select->setMaximumSize(60, 20);
      //select->resize(40, 20);	
      m_select->show();
      l->addWidget(m_select);

      connect(m_select, SIGNAL(clicked()), this, SLOT(selectColor()));
    }
		
    virtual ~ColorView() {}

    virtual void valueChange(const utils::Buffer& newValue)
    {
      m_current = reinterpret_cast<const char*>(newValue.getPtr());
      
      QColor newColor = stringToColor(m_current);

      m_select->setPalette(QPalette(newColor));
      QToolTip::add(this, m_current.c_str());
    }

private slots:
void selectColor()
    {
      QColor oldColor;
      if (m_current != "")
	  oldColor = stringToColor(m_current);

      if (!oldColor.isValid())
	  oldColor = QColor(128, 128, 128);
      
      QColor tmp 
	= QColorDialog::getColor ( oldColor, this, "ColorSelector") ;
		
    if (tmp.isValid())
      {
	std::string s = colorToString(tmp);

	utils::Buffer
	  bu(reinterpret_cast<const unsigned char*>(s.c_str()), s.length()+1);

	emit valueChanged(bu);
      }
    }

  private:

    QColor stringToColor(const std::string& s)
    {
      std::istringstream is(s);
      double r,g,b;

      is >> r >> g >> b;
			
      return QColor(static_cast<int>(r*255.0),
		    static_cast<int>(g*255.0),
		    static_cast<int>(b*255.0));
    }

    std::string colorToString(const QColor& col)
    {
	std::ostringstream os("");
	double r,g,b;

	r = (double) col.red()/255.;
	g = (double) col.green()/255.;
	b = (double) col.blue()/255.;

	os.precision(3);
	os << r << " " << g << " " << b;
			
	return os.str();
    }

    QButton* m_select;
    std::string m_current;
  };


  // constructor

  ColorViewConstructor::ColorViewConstructor()
    : TypeViewConstructor("color dialog", "color_selector")
  {
  }
	

  TypeView*
  ColorViewConstructor::construct(QWidget* parent,
				  const ParamMap& params) const
  {
    return new ColorView(parent, params);
  }

}

#include "colorview_moc_cpp.cpp"
