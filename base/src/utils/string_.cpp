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

#include "string_.h"

#include <iostream>

#include "xmlutils.h"

namespace utils
{
  
  String::String(const std::string& s)
    : m_data(s)
  {
  }

  String::String(const String& str)
    : m_data(str.m_data)
  {
  }

  const String& String::operator=(const String& str)
  {
    m_data = str.m_data;

    return *this;
  }

  std::ostream& operator<<(std::ostream& s, const utils::String& str)
  {
    s << "<str>";
    s << "<l>" << str.length() << "</l>";
    s << "<d>";
    for (const char* i = str.c_str(); i != str.c_str()+ str.length();++i)
      {
	s << *i;
      }
    s << "</d>";
    s << "</str>";

    return s;    
  }

  std::istream& operator>>(std::istream& s, utils::String& str)
  {
    checktag(s,"<str>");
    checktag(s,"<l>");
    unsigned int length; // bufferlength
    s >> length;
    checktag(s,"</l>");
    checktag(s,"<d>");
    std::string temp;
    for (unsigned int i = 0; i != length; ++i)
      {
	temp += s.get();
      }
    checktag(s,"</d>");
    checktag(s,"</str>");

    str = String(temp);

    return s;
  }
}
