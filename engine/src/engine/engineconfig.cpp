#include "engineconfig.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#if defined(OS_WIN32)
#include <windows.h>
#endif

#include "utils/configfile.h"
#include "utils/structreader.h"
#include "utils/filesystem.h"
#include "utils/autoptr.h"

namespace engine
{

  static std::string get_cfile_name()
  {
#if defined(OS_WIN32)
    return "../gephex.conf";
#elif defined(OS_POSIX)
    return std::string(getenv("HOME")) + "/.gephex/gephex.conf";
#endif		
  }

  static void dump(const EngineConfig& c, std::ostream& s)
  {
    s << "media_path           = " << c.media_path << "\n";
    s << "graph_path           = " << c.graph_path << "\n";
    s << "ipc_type             = " << c.ipcType << "\n";
    s << "ipc_unix_node_prefix = " << c.ipcUnixNodePrefix << "\n";
    s << "module_path          = " << c.module_path << "\n";
    s << "type_path            = " << c.type_path << "\n";
    s << "renderer_interval    = " << c.rendererInterval << "\n";
    s << "net_interval         = " << c.netInterval << "\n";
    s << "ipc_port             = " << c.port << "\n";
  }
  EngineConfig::EngineConfig()
  {
    std::string cfile_name = get_cfile_name();
    try
      {
        //	std::cout << "c started\n";
        //	std::cout << "got fname: " << cfile_name << "\n";
        utils::ConfigFile cf(cfile_name);
        //	std::cout << "created cf " << "\n";

	const utils::StructReader& common = cf.get_section("common");
	const utils::StructReader& engine = cf.get_section("engine");
	
        //	std::cout << "querying... " << "\n";
        graph_path        = engine.getStringValue("graph_path");
        ipcType           = engine.getStringValue("ipc_type","inet");
        ipcUnixNodePrefix = engine.getStringValue("ipc_unix_node_prefix",
						  "/tmp/gephex_socket");
        module_path       = engine.getStringValue("module_path");
        type_path         = engine.getStringValue("type_path");
        rendererInterval  = engine.getIntValue("renderer_interval", 35);
        netInterval       = engine.getIntValue("net_interval", 35);
        port              = engine.getIntValue("ipc_port", 666);

	media_path        = common.getStringValue("media_path");

	// This is a hack to communicate the media path to
	// loaded modules.
	static const char* GEPHEX_MEDIA_PATH = "GEPHEX_MEDIA_PATH";
#if defined(OS_POSIX)
	setenv(GEPHEX_MEDIA_PATH, media_path.c_str(), 1);
#elif defined(OS_WIN32)
	BOOL ret = SetEnvironmentVariable(GEPHEX_MEDIA_PATH,
									  media_path.c_str());
	if (ret == 0)
		throw std::runtime_error("Could not set GEPHEX_MEDIA_PATH");
#endif

#if (ENGINE_VERBOSITY > 0)
        dump(*this, std::cout);
#endif
      }
    catch (std::exception& e)
      {
        std::ostringstream os;
        os << cfile_name << " contains errors:\n" << e.what();
        throw std::runtime_error(os.str().c_str());
      }
  }
}
