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

  ConfigFile::ConfigFile(const std::string& file_name)
  {
    std::ifstream file(file_name.c_str());
    if (!file)
      throw std::invalid_argument("Could not open config file");

    StructList structs = divide_structs(file);
    
    for (StructList::const_iterator it = structs.begin();
	 it != structs.end(); ++it)
      {
	StructReaderPtr new_reader (new StructReader(*it));
	std::string name = new_reader->getName();

	if (m_sections.count(name) != 0)
	  {
	    throw std::invalid_argument("Duplicate section in config file");
	  }

	m_sections.insert(std::make_pair(name, new_reader));
      }
    
  }

  const StructReader& ConfigFile::get_section(const std::string& section_name)
  {
    SectionMap::iterator it = m_sections.find(section_name);
    if (it == m_sections.end())
      throw std::invalid_argument("Section not found");

    return *it->second;
  }
}

