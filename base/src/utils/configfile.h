#ifndef INCLUDED_CONFIG_FILE_H
#define INCLUDED_CONFIG_FILE_H

#include <string>
#include <map>

#include "autoptr.h"

namespace utils
{

  class StructReader;

  /**
   * Class that abstracts from parsing a config file.
   * The config file must consist of a sequence of c-structs
   * (see structreader.h).
   */
  class ConfigFile
  {
  public:
    /**
     * 
     * \param file_name the name of the config file
     * \throws std::invalid_argument if file_name can't be opened or
     *  parsed
     */
    ConfigFile(const std::string& file_name);

    /**
     * Returns one section of the config file.
     *
     * \returns a StructReader object that contains the section.
     *
     * \param section_name the name of the section
     *                     (i.e. the name of the c-struct)
     * \throw std::invalid_argument if this section does not exist
     */
    const StructReader& get_section(const std::string& section_name);

  private:
    typedef AutoPtr<StructReader> StructReaderPtr;
    typedef std::map<std::string, StructReaderPtr> SectionMap;
    SectionMap m_sections;
  };
}

#endif
