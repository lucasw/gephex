#include "engineconfig.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <fstream>
#include <sstream>

#include "utils/structreader.h"
#include "utils/filesystem.h"
#include "utils/autoptr.h"

namespace engine
{
  utils::StructReader EngineConfig::readConfigFile()
  {
    std::string fileName;
#if defined(OS_WIN32)
    fileName = "../enginew.conf";
#elif defined(OS_POSIX)
    std::string home = getenv("HOME");
    fileName = home + "/.gephex/engine.conf";
#endif
		
    std::ifstream file(fileName.c_str());

    std::string text;    
    if (!file)
      {
#if defined(OS_WIN32)
	throw std::runtime_error("can't find config file");
#elif defined(OS_POSIX)
	// create directory if necessary
	if (!utils::FileSystem::exists(home+"/.gephex"))
	  utils::FileSystem::makeDir(home+"/.gephex");

	// lets write a new one
	std::ofstream newConfig(fileName.c_str());
	if (!newConfig)
	  throw std::runtime_error("can't write config file");
	
	std::ostringstream newConfigStream;
	newConfigStream 
	  << "conf {" << std::endl
	  << "module_dirs=[" << INST_INSTALL_PREFIX 
          << "/lib/gephex/modules/]" << std::endl
	  << "type_dirs=[" << INST_INSTALL_PREFIX << "/lib/gephex/types/]" 
	  << std::endl
	  << "graph_dir=["<< home <<"/.gephex/graphs/]" << std::endl
	  << "sequence_dir=["<< home <<"/.gephex/sequences/]" << std::endl
	  << "playlist_dir=["<< home <<"/.gephex/playlists/]" << std::endl
	  << "ipc_type=[inet]" << std::endl
	  << "ipc_unix_node_prefix=[/tmp/gephex_socket_]" << std::endl
	  << "ipc_port=[6666]" << std::endl
	  << "}" << std::endl;

	text=newConfigStream.str();
	newConfig << text;
#endif
      }
    
    int i;
    //while((i = file.get()) && i != std::ifstream::traits_type::eof())
    while((i = file.get()) && i != EOF)
      {
	text += static_cast<char>(i);
      }
    
    file.close();
    
    return utils::StructReader(text);
}

  EngineConfig::EngineConfig()
    :sr(readConfigFile()),
     port(sr.getIntValue("ipc_port")),
     graphDir(sr.getStringValue("graph_dir")),
     sequDir(sr.getStringValue("sequence_dir")),
     plDir(sr.getStringValue("playlist_dir")),
     ipcType(sr.getStringValue("ipc_type","inet")),
     ipcUnixNodePrefix(sr.getStringValue("ipc_unix_node_prefix",
					 "/tmp/gephex_socket")),
     rendererInterval(sr.getIntValue("renderer_interval", 35)),
     netInterval(sr.getIntValue("net_interval", 35)),
     sequencerInterval(sr.getIntValue("sequencer_interval", 100)),
     moduleDirs(sr.getStringValue("module_dirs")),
     typeDirs(sr.getStringValue("type_dirs"))
  {
  }

}
