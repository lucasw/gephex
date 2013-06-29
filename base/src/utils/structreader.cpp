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

#include "structreader.h"

#include <iostream>
#include <sstream>

#include "istructtokenlistener.h"
#include "structscanner.h"

namespace utils
{

class MyListener : public IStructTokenListener
{
private:
  StructReader::ConfigMap& _map;
  std::string& _name;

public:
  MyListener(StructReader::ConfigMap& map, std::string& name)
    : _map(map), _name(name)
  {}

  virtual ~MyListener() {}

  virtual void beginStruct() {}
  virtual void endStruct() {}

  virtual void scannedStructName(const std::string& name)
  {
    _name = name;
  }

  virtual void scannedPair(const std::string& name,
			   const std::string& value, int)
  {
    StructReader::ConfigMap::const_iterator it = _map.find(name);
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

StructReader::StructReader(const ConfigMap& map)
 : m_values(map)
{
}

StructReader:: ~StructReader()
{
}

bool StructReader::find(const std::string& name, std::string& value) const
{
  ConfigMap::const_iterator it = m_values.find(name);

  if (it == m_values.end())
  {
	  return false;
  }

  value = it->second;
  return true;
}

std::string StructReader::getName() const
{
  return m_name;
}

bool StructReader::getBoolValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value;
  bool found = this->find(name, value);
  if (!found)
    throw std::runtime_error(std::string("Key '") + name + "' not found!");

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

double StructReader::getDoubleValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value;
  bool found = this->find(name, value);
  if (!found)
	  throw std::runtime_error(std::string("Key '") + name + "' not found!");
  
  std::istringstream s(value);
  double val;
  s >> val;

  if (!s)
    {
      std::string msg = "Ungueltiger Double Typ: name = '";
      msg += name + "', value = '" + value + "'";
      throw std::runtime_error(msg.c_str());
    }

  return val;
}

int StructReader::getIntValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value;
  bool found = this->find(name, value);
  if (!found)
	  throw std::runtime_error(std::string("Key '") + name + "' not found!");
  
  std::istringstream s(value);
  int val;
  s >> val;

  if (!s)
    {
      std::string msg = "Ungueltiger Int Typ: name = '";
      msg += name + "', value = '" + value + "'";
      throw std::runtime_error(msg.c_str());
    }

  return val;
}

std::string StructReader::getStringValue(const std::string& name) const
  throw (std::runtime_error)
{
  std::string value;
  bool found = this->find(name, value);
  if (!found)
	  throw std::runtime_error(std::string("Key '") + name + "' not found!");

  return value;
}


bool StructReader::getBoolValue(const std::string& name, bool defaultValue) const
{
	bool ret;
	try
	{
		ret = getBoolValue(name);
	}
	catch (...)
	{
		return defaultValue;
	}

	return ret;
}

double StructReader::getDoubleValue(const std::string& name,
				    double defaultValue) const
{
  std::string value;
  bool found = this->find(name, value);
  if (!found)
	  return defaultValue;
  else	
	  return getDoubleValue(name);
}

int StructReader::getIntValue(const std::string& name, int defaultValue) const
{
	int ret;
	try
	{
		ret = getIntValue(name);
	}
	catch (...)
	{
		return defaultValue;
	}

	return ret;
}

std::string StructReader::getStringValue(const std::string& name,
										 const std::string& defaultValue) const
{
	std::string ret;
	try
	{
		ret = getStringValue(name);
	}
	catch (...)
	{
		return defaultValue;
	}
  
	return ret;
}

StructReader::ConfigMap StructReader::getMap() const
{
	return m_values;
}

void StructReader::serialize(std::ostream& out) const
{
	out << m_name << " { ";
	for (ConfigMap::const_iterator it = m_values.begin();
		 it != m_values.end(); ++it)
	{
		out << it->first;
		out << "=[" << it->second << "]; ";
	}
	out << " } ";
	out.flush();
}

bool StructReader::has_value(const std::string& name) const
{
  return m_values.count(name) > 0;
}

} // end of namespace utils
