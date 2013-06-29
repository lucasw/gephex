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

#include "istructtokenlistener.h"

#include <sstream>

#include "structscanner.h"

class MyListener : public IStructTokenListener
{
private:
  std::map<std::string,std::string>& _map;
  std::string& _name;

public:
  MyListener(std::map<std::string,std::string>& map, std::string& name)
    : _map(map), _name(name)
  {}

  virtual ~MyListener() {}

  virtual void scannedStructName(const std::string& name)
  {
    _name = name;
  }

  virtual void scannedPair(const std::string& name,
			   const std::string& value)
  {
    std::map<std::string,std::string>::const_iterator it = _map.find(name);
    if (it != _map.end())
      {
	std::string msg = "Multiple Assignment for " + name;
	throw std::runtime_error(msg.c_str());
      }

    _map[name] = value;
  }
};

StructReader::StructReader(const std::string& text)
{
  MyListener listener(m_values, m_name);
  StructScanner scanner(listener);

  scanner.scan(text);
}

std::string StructReader::find(const std::string& name) const
{
  std::map<std::string,std::string>::const_iterator it = 
    m_values.find(name);

  if (it == m_values.end())
    throw std::runtime_error("Name existiert nicht");

  return it->second;
}

std::string StructReader::getName() const
{
  return m_name;
}

bool StructReader::getBoolValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value = find(name);

  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    {
      std::string msg = "Ungueltiger Bool Typ: name = ";
      msg += name + ", value = " + value;
      throw std::runtime_error(msg.c_str());
    }
}

int StructReader::getIntValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value = find(name);
  
  std::istringstream s(value);
  int val;
  s >> val;

  if (!s)
    {
      std::string msg = "Ungueltiger Int Typ: name = ";
      msg += name + ", value = " + value;
      throw std::runtime_error(msg.c_str());
    }

  return val;
}

std::string StructReader::getStringValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value = find(name);

  return value;
}

