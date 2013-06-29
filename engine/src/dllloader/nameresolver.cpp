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

#include "nameresolver.h"

#include <stdexcept>


NameResolver::NameResolver()
  : hash(), lastID(-1)
{
}

int NameResolver::registerObject(const std::string& name)
{
  /*  std::cout << "NameResolver:registerObject: name = \""
      << name << "\", size = " << hash.size() << std::endl;*/

  StringMap::const_iterator i = hash.find(name);
  if (i != hash.end())
    {
      throw std::runtime_error("Name existiert bereits");
    }

  hash[name] = ++lastID;

  return lastID;
}

int NameResolver::getObjectID(const std::string& name)
{
  /*std::cout << "NameResolver:getObjectID: name = \""
	    << name << "\", size = " << hash.size() << std::endl;

    std::cout << "{";
  for (StringMap::const_iterator i = hash.begin(); i != hash.end(); ++i)
    {
      std::cout << "<" << i->first << "," << i->second << ">";
      if (i->first == name)
	std::cout << " " << i->first << " == " << name;
      else
	std::cout << " " << i->first << " != " << name;
    }
    std::cout << "}" << std::endl;*/

  StringMap::const_iterator i = hash.find(name);
  if (i == hash.end())
    {
      //std::cout << "->Nicht gefunden!!!!" << std::endl;
      throw std::runtime_error("Ungültiger Name");
    }

  return (*i).second;
}

