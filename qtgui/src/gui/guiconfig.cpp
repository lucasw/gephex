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

#include "guiconfig.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <fstream>
#include <iostream>
#include <sstream>

#include "utils/configfile.h"
#include "utils/filesystem.h"
#include "utils/structreader.h"

namespace gui
{

  static std::string get_cfile_name()
  {
#if defined(OS_WIN32)
    return "../gephex.conf";
#elif defined(OS_POSIX)
    return std::string(getenv("HOME")) + "/.gephex/gephex.conf";
#endif		
  }
  
  GuiConfig::GuiConfig()
  {
    std::string cfile_name = get_cfile_name();
    try
      {
	utils::ConfigFile cf(cfile_name);
        const utils::StructReader& common = cf.get_section("common");
        const utils::StructReader& gui = cf.get_section("gui");

	media_path = common.getStringValue("media_path");
    
        ipcType = gui.getStringValue("ipc_type");
        if (ipcType == "inet")
          {
            ipcLocator = gui.getStringValue("ipc_inet_hostname");
          }
        else if (ipcType == "unix")
          {
            ipcLocator = gui.getStringValue("ipc_unix_node_prefix");
          }
    
        else if (ipcType == "namedpipe")
          {
            ipcLocator = gui.getStringValue("ipc_namedpipe_servername");
          }
        else
          {
            throw std::runtime_error("Unknown IPC Type: " + ipcType);
          }
    
        port = gui.getIntValue("ipc_port");

        engine_binary = gui.getStringValue("engine_binary");	
      }
    catch (std::exception& e)
      {
        std::ostringstream os;
        os << cfile_name << " contains errors:\n" << e.what();
        throw std::runtime_error(os.str().c_str());
      }
  }
}
