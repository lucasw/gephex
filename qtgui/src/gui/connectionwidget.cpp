#include "connectionwidget.h"
#include <cmath>
#include <qpainter.h>
#include <qwidget.h>
#include <math.h>

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


bool ConnectionWidget::isInside(QWidget* rel,const QPoint& y) const
{
  QPoint p1 = in.mapTo(rel,in.pos()) - in.pos();
  QPoint p2 = out.mapTo(rel,out.pos()) - out.pos();

  //TODO Bounding Box check

  // Richtungsvektor der Geraden
  double d1 = p2.x() - p1.x();
  double d2 = p2.y() - p1.y();

  // Normalenvektor ausrechnen
  double n1;
  double n2;

  if (d1 == 0)
    {
      n1 = 1.;
      n2 = 0.;
    }
  else 
    {
      double alpha = d2 / d1;
      n1 = sin(alpha);
      n2 = cos(alpha);
    }

  double b;
  double a;
  if (fabs(n1 - 0.) < 0.0000001)
    {
      b = (y.x() - p1.x()) / d1;
      a = (p1.y() - y.y() + d2 * b) / n2;
    }
  else
    {
      b = (y.y() - p1.y() + (n2/n1)*(p1.x()-y.x())) / (d2 - (n2/n1)*d1);

      a = (p1.x() - y.x() + d1*b) / n1;
    }

  if (b < 0 || b > 1) // Innerhalb der Geraden?
    return false;

  if (fabs(a) < 7) // Nah genug dran?
    return true;

  return false;
}

void ConnectionWidget::draw(QWidget* rel, QPainter& painter) const
{
  painter.drawLine(in.mapTo(rel,in.pos())-in.pos(),
		   out.mapTo(rel,out.pos())-out.pos());
}

} // end of namespace gui
