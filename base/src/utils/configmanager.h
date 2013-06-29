/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#ifndef INCLUDED_CONFIGMANAGER_H
#define INCLUDED_CONFIGMANAGER_H

#include <string>
#include <list>
#include <map>

#include "autoptr.h"


//#include "utils/configfile.h"
namespace utils
{
  class ConfigFile;

  struct config_param_t
  {
    enum ParamType {BOOL_PARAM, INT_PARAM, STRING_PARAM };

    union ParamValue { bool b; int i; const char* s; };

    config_param_t(const std::string& name,
                   ParamType type,
                   const std::string& section,
                   const std::string& description,
                   ParamValue* def);

    std::string m_name;
    ParamType   m_type;
    std::string m_section;
    std::string m_description;

    bool        m_required;
    ParamValue  m_default;
  };

  class ConfigManager
    {    
    public:
      typedef std::list<config_param_t> ParamList;
      typedef utils::AutoPtr<utils::ConfigFile> ConfigFilePtr;
      typedef std::map<std::string, config_param_t> CPMap;

      ConfigManager(const std::string& cfile_name,
                   int argc, const char* argv[],
                   const ParamList& params);

      ConfigManager(const ConfigManager& c);

      ~ConfigManager();

      /*!
       * True iff the first cmdline parameter was "--help" or "-h"
       */
      bool        help_requested() const;

      bool        get_bool_param(const std::string& param_name)   const;
      int         get_int_param(const std::string& param_name)    const;
      std::string get_string_param(const std::string& param_name) const;

    private:
      ParamList m_params;
      ConfigFilePtr m_cf_file;
      ConfigFilePtr m_cf_cmdl;

      CPMap m_cpm;

      bool m_help_requested;
    };
}

#endif
