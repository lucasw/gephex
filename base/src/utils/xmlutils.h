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

#ifndef INCLUDED_XML_UTILS_H
#define INCLUDED_XML_UTILS_H

#include <iosfwd>
#include <string>

namespace utils
{
  void checktag(std::istream& s,const std::string& giventag);

  bool checktagloop(std::istream& s,const std::string& looptag,
                    const std::string& exittag);

  void extractbetweenTags(std::istream& s,std::string& extracted);

  namespace xml
  {
    typedef std::string::const_iterator Iterator;
    Iterator tagOpens(Iterator begin, 
                  Iterator end,
                  const std::string& tag_name);

    Iterator tagCloses(Iterator begin,
                   Iterator end,
                   const std::string& tag_name);

    Iterator leafTag(Iterator begin,
                 Iterator end,
                 const std::string& tag_name,
                 std::string& b);

    /**
     * Returns the name of the next tag.
     * Note: for a closing tag "</xxx>" the string "/xxx" is returned.
     */
    std::string next_tag_name(Iterator begin, Iterator end);
  }
}

#endif
