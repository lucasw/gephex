#include "point.h"

#include <iostream>

namespace gui 
{

  bool operator==(const Point& p1, const Point& p2)
  {
    return (p1.x() == p2.x() && p1.y() == p2.y());
  }

  std::ostream& operator<<(std::ostream& s, const Point& p)
  {
    s << p.x() << ' ' << p.y();

	return s;
  }

  std::istream& operator>>(std::istream& s, Point& p)
  {
    int x, y;
    s >> x >> y;

    p = Point(x,y);

	return s;
  }


}
