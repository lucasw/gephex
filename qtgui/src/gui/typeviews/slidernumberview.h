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

#ifndef INCLUDE_SLIDER_NUMBER_VIEW_H
#define INCLUDE_SLIDER_NUMBER_VIEW_H

#include "gui/typeview.h"

#include <cassert>
#include <cmath>
#include <sstream>

#include <QtGui/QBoxLayout>
#include <QtGui/QDial>
#include <QtGui/QSlider>

#include "utils/buffer.h"
#include "utils/structreader.h"

namespace gui {
class HSliderNumberViewConstructor : public TypeViewConstructor {
public:
  HSliderNumberViewConstructor();
  virtual TypeView *construct(QWidget *parent, const ParamMap &) const;
};

class VSliderNumberViewConstructor : public TypeViewConstructor {
public:
  VSliderNumberViewConstructor();
  virtual TypeView *construct(QWidget *parent, const ParamMap &) const;
};

class DialNumberViewConstructor : public TypeViewConstructor {
public:
  DialNumberViewConstructor();
  virtual TypeView *construct(QWidget *parent, const ParamMap &) const;
};

static const int RESOLUTION = 255;
class SchlonzNumberView : public gui::TypeView {
  Q_OBJECT

public:
  SchlonzNumberView(QWidget *parent, Qt::Orientation orient, bool isDial,
                    const ParamMap &params)
      : TypeView(parent, params), m_setValueCalled(false) {
    utils::StructReader sr(params);
    m_lowVal = sr.getDoubleValue("lower_bound", 0);
    double highVal = sr.getDoubleValue("higher_bound", 1);

    m_scale = (highVal - m_lowVal) / static_cast<double>(RESOLUTION);
    if (m_scale == 0)
      m_scale = 1;

    if (!isDial)
      m_slider = new QSlider(orient, this);
    else
      m_slider = new QDial(this);

    m_slider->setMinimum(0);
    m_slider->setMaximum(RESOLUTION);
    m_slider->setPageStep(1);
    m_slider->setValue(0);

    m_layout->addWidget(m_slider);

    connect(m_slider, SIGNAL(valueChanged(int)), this,
            SLOT(sliderChanged(int)));
  }

  virtual void valueChange(const utils::Buffer &newValue) {

    std::istringstream is(reinterpret_cast<const char *>(newValue.getPtr()));

    double raw = 0;
    is >> raw;
    double d = (raw - m_lowVal) / m_scale;

    if (d < 0)
      d = 0;
    else if (d > RESOLUTION)
      d = RESOLUTION;

    const int newVal = static_cast<int>(floor(d + 0.5));

    /*printf("valueChange(), str='%s', value=%i, newValue=%i\n",
      reinterpret_cast<const char*>(newValue.getPtr()),
      m_slider->value(), newVal);*/

    if (newVal != m_slider->value()) {
      // printf("Setting slider value\n");
      m_setValueCalled = true;
      m_slider->setValue(newVal);
    }
  }

private slots:
  void sliderChanged(int newVal) {
    /*printf("sliderChanged( %i ), value=%i, m_setValueCalled=%i\n",
      newVal, m_slider->value(), m_setValueCalled);*/

    if (!m_setValueCalled) {
      const double scaled = newVal * m_scale + m_lowVal;

      std::ostringstream s;
      s << scaled;
      const std::string data = s.str();
      const unsigned char *udata =
          reinterpret_cast<const unsigned char *>(data.c_str());

      // printf("sending '%s'\n", s.str().c_str());

      emit valueChanged(utils::Buffer(udata, data.length() + 1));
    } else {
      m_setValueCalled = false;
    }

    /*printf("after: value=%i, m_setValueCalled=%i\n",
      m_slider->value(), m_setValueCalled);*/
  }

private:
  QAbstractSlider *m_slider;
  bool m_setValueCalled;
  double m_lowVal;
  double m_scale;
};

} // namespace gui

#endif
