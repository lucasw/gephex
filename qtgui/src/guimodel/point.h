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
