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

#ifndef INCLUDED_CONFIG_FILE_H
#define INCLUDED_CONFIG_FILE_H

#include <string>
#include <map>

#include <iosfwd>

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
     * \param config_stream a stream that contains the config
     *
     * \throw std::invalid_argument if parsing the stream fails
     */
    ConfigFile(std::istream& config_stream);

    ~ConfigFile();

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
