#include "guiconfig.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <fstream>
#include <iostream>
#include <sstream>

#include "utils/filesystem.h"



namespace gui
{
  
  std::string defaultConfig()
  {
    std::ostringstream defConf;
    defConf << "conf {" << std::endl;
    defConf << "ipc_type=[inet]" << std::endl;
    defConf << "ipc_unix_node_prefix=[/tmp/gephex_socket_]" << std::endl;
    defConf << "ipc_inet_hostname=[localhost]" << std::endl;
    defConf << "ipc_port=[6666]" << std::endl;
    defConf << "}" << std::endl;
    return defConf.str();
  }


  typedef utils::StructReader::ConfigMap ConfigMap;


  GuiConfig createGuiConfig()
  {
    std::string configFileName;
#ifdef OS_WIN32
    configFileName = "../guiw.conf";
#endif
#ifdef OS_POSIX
    std::string home = getenv("HOME");
    configFileName = home + "/.gephex/gui.conf";
#endif

    // try to open config file
    std::ifstream file(configFileName.c_str());
    std::string configString;
    if (!file)
      {
     	// could not open configfile
#ifdef OS_WIN32
	// Windows user exit here
	throw std::runtime_error("could not open configfile");
#endif
#ifdef OS_POSIX
	// check if gephex dir is here if not create one
	if (!utils::FileSystem::exists(home+"/.gephex"))
	  utils::FileSystem::makeDir(home+"/.gephex");

	// try write default file
	std::ofstream defaultFile(configFileName.c_str());
	if (!defaultFile)
	  {
	    throw std::runtime_error("could not write default config file:" 
				     + configFileName);
	  }
	else
	  {
	    configString = defaultConfig();
	    defaultFile << configString;
	    file.close();
	  }
#endif
      }
    else
      {
	// file is opened now
	// lets now read all the file in the string
	int i;
	
	//while((i = file.get()) && i != std::ifstream::traits_type::eof())
	while((i = file.get()) && i != EOF)
	  {
	    configString += static_cast<char>(i);
	  }
      }
    
    GuiConfig config;
    config.sr = StructReaderPtr(new utils::StructReader(configString));
    
    config.ipcType = config.sr->getStringValue("ipc_type");
    if (config.ipcType == "inet")
      {
	config.ipcLocator = config.sr->getStringValue("ipc_inet_hostname");
      }
    else if (config.ipcType == "unix")
      {
	config.ipcLocator = config.sr->getStringValue("ipc_unix_node_prefix");
      }
    
    else if (config.ipcType == "namedpipe")
      {
	config.ipcLocator = config.sr->getStringValue("ipc_namedpipe_servername");
      }
    else
      {
	throw std::runtime_error("Unknown IPC Type: " + config.ipcType);
      }
    
    config.port = config.sr->getIntValue("ipc_port");

    return config;
  }

}

