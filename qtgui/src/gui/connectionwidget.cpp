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

#include "connectionwidget.h"

#include <math.h>

#include <QtGui/QWidget>
#include <QtGui/QPainter>

#include "inputplugwidget.h"
#include "outputplugwidget.h"

namespace gui
{

  ConnectionWidget::ConnectionWidget( InputPlugWidget& _in,
                                      OutputPlugWidget& _out)
    : in(_in), out(_out)
  {
    //setBackgroundMode(PaletteForeground);
  }

  static QPoint global_pos(const QWidget& w)
  {
    QWidget* parent = w.parentWidget();

    QPoint rel_pos = w.pos();

    if (parent == 0)
      return rel_pos;

    return parent->mapToGlobal(rel_pos);
  }

  QPoint mid_point_global(const QWidget& w)
  {
    return global_pos(w) + QPoint(w.width()/2, w.height()/2);
  }

  double euklid(const QPoint& p1, const QPoint& p2)
  {
    float dx = static_cast<float>(p2.x() - p1.x());
    float dy = static_cast<float>(p2.y() - p1.y());

	return sqrt(dx*dx + dy*dy);
  }

  double ConnectionWidget::dist(const QPoint& y) const
  {
    QPoint p1 = mid_point_global(in);
    QPoint p2 = mid_point_global(out);

    // Richtungsvektor der Geraden
    double d1 = p2.x() - p1.x();
    double d2 = p2.y() - p1.y();

    // Normalenvektor ausrechnen
    double n1 = -d2;
    double n2 = d1;

    double ln = sqrt(n1*n1 + n2*n2);
    n1 /= ln;
    n2 /= ln;

    double p1y1 = y.x() - p1.x();
    double p1y2 = y.y() - p1.y();

    double dist = fabs(p1y1 * n1 + p1y2 * n2);

    double ld = sqrt(d1*d1 + d2*d2);
    d1 /= ld;
    d2 /= ld;
    double k = p1y1 * d1 + p1y2 * d2;

    if (k < 0)
      return euklid(p1, y);
    else if (k > ld)
      return euklid(p2, y);

    return dist;
  }

  void ConnectionWidget::draw(QWidget* rel, QPainter& painter) const
  {
    QPoint in_pos  = rel->mapFromGlobal(mid_point_global(in));
    QPoint out_pos = rel->mapFromGlobal(mid_point_global(out));
    painter.drawLine(in_pos, out_pos);
  }

} // end of namespace gui
