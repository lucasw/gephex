#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H

#include <iosfwd>

namespace gui
{

class Point
{
	int m_x;
	int m_y;
public:
	explicit Point(int x = 0, int y = 0) : m_x(x), m_y(y) { }
	int x() const { return m_x; }
	int y() const { return m_y; }
	
};

bool operator==(const Point& p1, const Point& p2);

 std::ostream& operator<<(std::ostream& s, const Point& p);
 std::istream& operator>>(std::istream& s, Point& p);

}
#endif
