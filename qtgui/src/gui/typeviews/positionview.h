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

#ifndef INCLUDED_POSITION_VIEW_H
#define INCLUDED_POSITION_VIEW_H

#include "gui/typeview.h"

#include <iostream>
#include <sstream>

#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/qlayout.h>

#include "utils/buffer.h"

namespace gui {
class KleinesFeld : public QWidget {
  Q_OBJECT
public:
  KleinesFeld(QWidget *parent, const QSize &preferredSize,
              const QSize &minimumSize);

  void setPos(const QPoint &p);

  QPoint pos() const { return m_pos; }

  QSize sizeHint() const { return m_preferredSize; }

  QSize minimumSizeHint() const { return m_minimumSize; }

signals:
  void posChanged(const QPoint &);

protected:
  void paintEvent(QPaintEvent *pe);
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

private:
  void drawCuteLittleCross(const QPoint &p, QPainter &painter);

  QPoint m_pos;
  QSize m_preferredSize;
  QSize m_minimumSize;
};

class PositionView : public gui::TypeView {
  Q_OBJECT
public:
  PositionView(QWidget *parent, const ParamMap &params)
      : TypeView(parent, params), m_setValueCalled(false) {
    static const int PREFERRED_WIDTH = 160;
    static const int PREFERRED_HEIGHT = 120;
    static const int MIN_WIDTH = 40;
    static const int MIN_HEIGHT = 30;

    m_mausFresser =
        new KleinesFeld(this, QSize(PREFERRED_WIDTH, PREFERRED_HEIGHT),
                        QSize(MIN_WIDTH, MIN_HEIGHT));

    m_mausFresser->setSizeIncrement(4, 3);

    m_layout->addWidget(m_mausFresser);
    m_mausFresser->show();

    connect(m_mausFresser, SIGNAL(posChanged(const QPoint &)), this,
            SLOT(kleinesfeldChanged(const QPoint &)));
  }

  virtual void valueChange(const utils::Buffer &newValue) {
    std::istringstream is(reinterpret_cast<const char *>(newValue.getPtr()));

    double x;
    double y;
    is >> x;
    is >> y;

    QPoint newPos = QPoint(static_cast<int>(m_mausFresser->width() * x + 0.5),
                           static_cast<int>(m_mausFresser->height() * y + 0.5));

    if (m_mausFresser->pos() != newPos) {
      m_setValueCalled = true;
      m_mausFresser->setPos(newPos);
    }
  }

public slots:
  void kleinesfeldChanged(const QPoint &p) {
    if (!m_setValueCalled) {
      if (p.x() < 0 || p.x() >= width() || p.y() < 0 || p.y() >= height()) {
        return;
      }

      double x = ((double)p.x() / m_mausFresser->width());
      double y = ((double)p.y() / m_mausFresser->height());

      std::ostringstream os;

      os << x << " " << y;
      const std::string str = os.str();
      const char *txt = str.c_str();
      utils::Buffer b = utils::Buffer(
          reinterpret_cast<const unsigned char *>(txt), str.length() + 1);
      emit valueChanged(b);
    } else {
      m_setValueCalled = false;
    }
  }

private:
  KleinesFeld *m_mausFresser;
  bool m_setValueCalled;
};

class PositionViewConstructor : public TypeViewConstructor {
public:
  PositionViewConstructor();
  virtual TypeView *construct(QWidget *parent, const ParamMap &params) const;
};
} // namespace gui
#endif
