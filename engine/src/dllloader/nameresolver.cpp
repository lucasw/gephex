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

