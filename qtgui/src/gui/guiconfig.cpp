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
