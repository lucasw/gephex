#include "structreader.h"

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

std::string StructReader::find(const std::string& name) const
{
  ConfigMap::const_iterator it = 
    m_values.find(name);

  if (it == m_values.end())
  {
	  std::string msg = "Variable ";
	  msg += name + " existiert nicht.";
    throw std::runtime_error(msg.c_str());
  }

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

} // end of namespace utils
