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

#include "slidernumberview.h"

#include <sstream>
#include <cmath>
#include <cassert>

#include <qslider.h>
#include <qlayout.h>
//#include <qmessagebox.h>

#include "utils/buffer.h"
#include "utils/structreader.h"

namespace gui
{

  static const int RESOLUTION = 255;
  class SliderNumberView : public gui::TypeView
  {
    Q_OBJECT
    
  public:
    SliderNumberView(QWidget* parent, Qt::Orientation orient,
		     const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false), m_value(0)
    {
      if (orient == QSlider::Vertical)
	{
	  this->resize(24, 100);
	}
      else
	{
	  this->resize(100,24);
	}

      utils::StructReader sr(params);
      m_lowVal    = sr.getDoubleValue("lower_bound", 0);
      m_highVal   = sr.getDoubleValue("higher_bound", 1);
	
      m_slider = new QSlider(0, RESOLUTION, 1, 0, orient, this, "slider");
	
      QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,0);
      layout->addWidget(m_slider);

      connect(m_slider, SIGNAL(valueChanged(int)),
	      this, SLOT(sliderChanged(int)));
    }

    virtual void valueChange(const utils::Buffer& newValue) {

      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw = 0;
      is >> raw;
      double d = (raw - m_lowVal) / (m_highVal - m_lowVal) * RESOLUTION;

      if (d < 0)
		  d = 0;
      else if (d > RESOLUTION)
		  d = RESOLUTION;

      if (fabs(d - m_value) > 0.00001)
	  {
		  m_setValueCalled = true;
		  m_value = d;
		  m_slider->setValue(static_cast<int>(d));
	  }
    }

private slots:
    void sliderChanged(int newVal)
    {      	
	  if (!m_setValueCalled)
	  {
		  double i = newVal / (double) RESOLUTION;
		  i = i * (m_highVal - m_lowVal) + m_lowVal;
		  
		  if (fabs(i - m_value) > 0.00001)
		  {
			  std::ostringstream s;
			  s << i;
			  std::string data = s.str();
			  const unsigned char*
				  udata = reinterpret_cast<const unsigned char*>(data.c_str());
			  emit valueChanged(utils::Buffer(udata, data.length()+1));	
		  }
	  }
	  else
	  {
		  m_setValueCalled = false;
	  }
    }

  private:
    QSlider* m_slider;
	bool m_setValueCalled;
    double m_value;
    double m_lowVal;
    double m_highVal;
  };




  HSliderNumberViewConstructor::HSliderNumberViewConstructor()
    : TypeViewConstructor("horizontal slider", "hslider") {}

  TypeView* HSliderNumberViewConstructor::construct(QWidget* parent,
					   const ParamMap& params) const
  {
    return new SliderNumberView(parent, QSlider::Horizontal, params);
  }
 

  VSliderNumberViewConstructor::VSliderNumberViewConstructor()
    : TypeViewConstructor("vertical slider", "vslider") {}

  TypeView* VSliderNumberViewConstructor::construct(QWidget* parent,
					   const ParamMap& params) const
  {
    return new SliderNumberView(parent, QSlider::Vertical, params);
  }

}

#include "slidernumberview_moc_cpp.cpp"
