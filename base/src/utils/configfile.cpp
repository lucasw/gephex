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

#include "configfile.h"

#include <list>
#include <stdexcept>
#include <fstream>

#include "structreader.h"

namespace utils
{
  typedef std::list<std::string> StructList;

  static StructList divide_structs(std::istream& s)
  {
    StructList l;
    int level = 0;
    std::string current;
    
    int i;
    while((i = s.get()) && i != EOF)
      {
	char c = static_cast<char>(i);
	current += c;
	if (c == '{')
	  {
	    ++level;
	  }
	else if (c == '}')
	  {
	    --level;
	    if (level == 0)
	      {
		l.push_back(current);
		current = "";
	      }
	  }
	if (level < 0)
	  throw std::invalid_argument("Too many closing braces");
      }

    if (level > 0)
      throw std::invalid_argument("Too many opening braces");

    assert(level == 0);
    return l;
  }

  ConfigFile::ConfigFile(std::istream& config_stream)
  {
    StructList structs = divide_structs(config_stream);
    
    for (StructList::const_iterator it = structs.begin();
	 it != structs.end(); ++it)
      {
	StructReaderPtr new_reader (new StructReader(*it));
	std::string name = new_reader->getName();

	if (m_sections.count(name) != 0)
	  {
	    throw std::invalid_argument("Duplicate section in config");
	  }

	m_sections.insert(std::make_pair(name, new_reader));
      }
    
  }

  ConfigFile::~ConfigFile()
  {
  }

  const StructReader& ConfigFile::get_section(const std::string& section_name)
  {
    SectionMap::iterator it = m_sections.find(section_name);
    if (it == m_sections.end())
      throw std::invalid_argument("Section not found");

    return *it->second;
  }
}

