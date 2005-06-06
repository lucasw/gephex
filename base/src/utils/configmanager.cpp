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

#include "configmanager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "configfile.h"
#include "structreader.h"

namespace utils
{

  static void dump(const ConfigManager& c, std::ostream& s,
                   const ConfigManager::ParamList& params)
  {
    for (ConfigManager::ParamList::const_iterator it = params.begin();
         it != params.end(); ++it)
      {
        s << "  " << it->m_name << "\t= ";

        if (it->m_type == config_param_t::BOOL_PARAM)
          s << c.get_bool_param(it->m_name);
        else if (it->m_type == config_param_t::INT_PARAM)
          s << c.get_int_param(it->m_name);
        else if (it->m_type == config_param_t::STRING_PARAM)
          s << c.get_string_param(it->m_name);

        s << "\n";
      }
  }

  static void print_param_value(std::ostream& s,
                                config_param_t::ParamValue val,
                                config_param_t::ParamType type)
  {
    switch(type)
      {
      case config_param_t::BOOL_PARAM:   s << val.b; break;
      case config_param_t::INT_PARAM:    s << val.i; break;
      case config_param_t::STRING_PARAM: s << val.s; break;
      }
  }

  static void print_help(const std::string& my_name,
                         const ConfigManager::ParamList& params)
  {
    std::cout << "Usage: " << my_name << " [options]\n"
              << "The allowed options are:\n";

    for (ConfigManager::ParamList::const_iterator it = params.begin();
         it != params.end(); ++it)
      {
        std::cout << "  --" << it->m_name << "\t"
                  << it->m_description << "\n";

        if (!it->m_required)
          {
            std::cout << "\t\t\tdefault=[";
            print_param_value(std::cout, it->m_default, it->m_type);
            std::cout << "]\n";
          }
        
      }
  }

  static void check_type(const utils::StructReader& sr,
                         const std::string& name,
                         config_param_t::ParamType type)
  {
    switch (type)
      {
      case config_param_t::BOOL_PARAM:
        sr.getBoolValue(name);  break;
      case config_param_t::INT_PARAM:
        sr.getIntValue(name);  break;
      case config_param_t::STRING_PARAM:
        sr.getStringValue(name);  break;
      }
  }

  static void check_cf_file(const ConfigManager::ParamList& params,
                            ConfigManager::ConfigFilePtr cf)
  {
    for (ConfigManager::ParamList::const_iterator it = params.begin();
         it != params.end(); ++it)
      {
        const config_param_t& current = *it;

        const utils::StructReader& sr = cf->get_section(current.m_section);
        
        if (current.m_required || sr.has_value(current.m_name))
          check_type(sr, current.m_name, current.m_type);
      }
  }


  static bool is_help(const std::string& arg)
  {
    return arg == "--help" || arg == "-h";
  }
  
  static bool is_param(const std::string& arg)
  {
    if (arg.length() < 3)
      return false;

    if (!(arg[0] == '-' && arg[1] == '-'))
      return false;

    if (arg.find('=') == std::string::npos)
      return false;

    return true;
  }

  static void create_cmdl_config(std::ostream& os,
                                 const ConfigManager::ParamList& params,
                                 int argc, const char* argv[],
				 bool& help_requested)
  {
    os << "cmdl {\n";

    for (int i = 1; i < argc; ++i)
      {
        std::string arg = argv[i];

        if (is_help(arg))
          {
            print_help(argv[0], params);
	    help_requested = true;
          }
        else if (is_param(arg))
          os << arg.substr(2) << "\n"; // strip leading "--"
        else
          {
	    std::stringstream strs;

	    strs << "Invalid argument: '" << arg << "'\n";

            print_help(argv[0], params);

            throw std::runtime_error(strs.str().c_str());
          }
      }
    
    os << "}";
  }

  static void check_cf_cmdl(const ConfigManager::ParamList& /*params*/,
                            ConfigManager::ConfigFilePtr cf,
                            const ConfigManager::CPMap& cpm)
  {
    const utils::StructReader& sr = cf->get_section("cmdl");
    const utils::StructReader::ConfigMap& m = sr.getMap();

    for (utils::StructReader::ConfigMap::const_iterator it = m.begin();
         it != m.end(); ++it)
      {
        std::string param_name  = it->first;

        ConfigManager::CPMap::const_iterator cit = cpm.find(param_name);

        if (cit == cpm.end())
          throw std::runtime_error("Unknown cmdl parameter: '--"
                                   + param_name + "'");

        check_type(sr, param_name, cit->second.m_type);
      }
  }

  config_param_t::config_param_t(const std::string& name, ParamType type,
                                 const std::string& section,
                                 const std::string& description,
                                 ParamValue* def)
    : m_name(name), m_type(type), m_section(section),
      m_description(description), m_required(def == 0)
  {
    if (def)
      m_default = *def;
  }

  ConfigManager::ConfigManager(const std::string& cfile_name,
                             int argc, const char* argv[],
                             const ParamList& params)
    : m_params(params), m_cf_file(0), m_cf_cmdl(0), m_help_requested(false)
  {
    for (ConfigManager::ParamList::const_iterator it = params.begin();
         it != params.end(); ++it)
      {
        if (m_cpm.count(it->m_name) != 0)
          throw std::runtime_error("Duplicate parameter name: '" +
                                   it->m_name + "'");

        m_cpm.insert(std::make_pair(it->m_name, *it));
      }

    try
      {
        std::ifstream cfile(cfile_name.c_str());

        //        std::cout << "c started\n";
        //        std::cout << "got fname: " << cfile_name << "\n";
        m_cf_file = ConfigFilePtr(new utils::ConfigFile(cfile));
        //        std::cout << "created cf " << "\n";
               
        check_cf_file(m_params, m_cf_file);

        //        std::cout << "processing cmdl...\n";
        std::ostringstream ccmdl;
        create_cmdl_config(ccmdl, m_params, argc, argv, m_help_requested);

        std::istringstream ccmdl_is(ccmdl.str().c_str());

        m_cf_cmdl = ConfigFilePtr(new utils::ConfigFile(ccmdl_is));

        check_cf_cmdl(m_params, m_cf_cmdl, m_cpm);

	if (!help_requested())
	  dump(*this, std::cout, m_params);
      }
    catch (std::exception& e)
      {
        std::ostringstream os;
        os << "error while processing '" << cfile_name << "':\n" << e.what();
        throw std::runtime_error(os.str().c_str());
      }

    //    std::cout << "c done\n";
  }

  ConfigManager::ConfigManager(const ConfigManager& c)
    : m_params(c.m_params), m_cf_file(c.m_cf_file), m_cf_cmdl(c.m_cf_cmdl),
      m_cpm(c.m_cpm)
  {
  }

  ConfigManager::~ConfigManager()
  {
  }

  bool ConfigManager::help_requested() const
  {
    return m_help_requested;
  }

  bool ConfigManager::get_bool_param(const std::string& param_name) const
  {
    CPMap::const_iterator it = m_cpm.find(param_name);
    if (it == m_cpm.end())
      throw std::runtime_error("Invalid param '" + param_name + "'");

    if (it->second.m_type != config_param_t::BOOL_PARAM)
      throw std::runtime_error("Param '" + param_name + "' is not a bool");

    const utils::StructReader& cmdl   = m_cf_cmdl->get_section("cmdl");

    if (cmdl.has_value(param_name))
      return cmdl.getBoolValue(param_name);
    else 
      {
        std::string section = it->second.m_section;
        const utils::StructReader& sr = m_cf_file->get_section(section);

        if (it->second.m_required)
          return sr.getBoolValue(param_name);
        else
          return sr.getBoolValue(param_name, it->second.m_default.b);
      }
  }

  int ConfigManager::get_int_param(const std::string& param_name) const
  {
    CPMap::const_iterator it = m_cpm.find(param_name);
    if (it == m_cpm.end())
      throw std::runtime_error("Invalid param '" + param_name + "'");

    if (it->second.m_type != config_param_t::INT_PARAM)
      throw std::runtime_error("Param '" + param_name + "' is not an int");

    const utils::StructReader& cmdl   = m_cf_cmdl->get_section("cmdl");

    if (cmdl.has_value(param_name))
      return cmdl.getIntValue(param_name);
    else 
      {
        std::string section = it->second.m_section;
        const utils::StructReader& sr = m_cf_file->get_section(section);

        if (it->second.m_required)
          return sr.getIntValue(param_name);
        else
          return sr.getIntValue(param_name, it->second.m_default.i);
      }
  }

  std::string ConfigManager::get_string_param(const std::string& param_name)
    const
  {
    CPMap::const_iterator it = m_cpm.find(param_name);
    if (it == m_cpm.end())
      throw std::runtime_error("Invalid param '" + param_name + "'");

    if (it->second.m_type != config_param_t::STRING_PARAM)
      throw std::runtime_error("Param '" + param_name + "' is not a string");

    const utils::StructReader& cmdl   = m_cf_cmdl->get_section("cmdl");

    if (cmdl.has_value(param_name))
      return cmdl.getStringValue(param_name);
    else 
      {
        std::string section = it->second.m_section;
        const utils::StructReader& sr = m_cf_file->get_section(section);

        if (it->second.m_required)
          return sr.getStringValue(param_name);
        else
          return sr.getStringValue(param_name, it->second.m_default.s);
      }
  }
}
