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
#include <cmath>

#include <QtGui/QLayout>
#include <QtGui/QPushButton>

#include <QtGui/QColorDialog>

namespace gui
{

  class ColorView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    ColorView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_current("")
    {
      m_select = new QPushButton(this);
      m_select->setAutoFillBackground(true);

      m_layout->addWidget(m_select);
      m_select->show();

      connect(m_select, SIGNAL(clicked()), this, SLOT(selectColor()));
    }
		
    virtual ~ColorView() {}

    virtual void valueChange(const utils::Buffer& newValue)
    {
      m_current = reinterpret_cast<const char*>(newValue.getPtr());
      
      QColor newColor = stringToColor(m_current);

      m_select->setPalette(QPalette(newColor));
      setToolTip(m_current.c_str());
    }

private slots:
    void selectColor()
    {
      QColor oldColor;
      if (m_current != "")
	  oldColor = stringToColor(m_current);

      if (!oldColor.isValid())
	  oldColor = QColor(128, 128, 128);
      
      QColor tmp = QColorDialog::getColor(oldColor, this) ;
		
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
			
      return QColor(static_cast<int>(floor(r*255 +.5)),
		    static_cast<int>(floor(g*255 +.5)),
		    static_cast<int>(floor(b*255 +.5)));
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

    QAbstractButton* m_select;
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
