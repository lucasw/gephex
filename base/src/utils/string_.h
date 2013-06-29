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

#ifndef INCLUDED_STRING__H
#define INCLUDED_STRING__H

#include <string>
#include <iosfwd>

namespace utils
{

  /**
   * This is a string class that supports serialization and deserialization
   * to and from a stream via the standard << and >> operators.
   * std::string does not support this, for example:
   *
   *    std::string s("Hallo Kinderchen");
   *    stream << s;
   *    std:.string s2;
   *    stream >> s2;
   *    assert(s1 == s2);
   *
   *    The assertion will fail, s2 will just be "Hallo".
   */
  class String
  {
  public:
    String(const std::string& str = "");
    String(const String&);

    const String& operator=(const String&);

    std::string::size_type length() const { return m_data.length(); }

    const char* c_str() const{ return m_data.c_str(); }

    operator std::string() const { return m_data; }

    bool operator==(const String&s)
    {
      return m_data == s.m_data;
    }

    bool operator!=(const String&s)
    {
      return m_data != s.m_data;
    }

  private:

    std::string m_data;
  };

  std::ostream& operator<<(std::ostream& s, const utils::String& str);
  std::istream& operator>>(std::istream& s, utils::String& str);
}

#endif
