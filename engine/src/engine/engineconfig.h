#ifndef INCLUDED_ENGINECONFIG_H
#define INCLUDED_ENGINECONFIG_H

#include <string>

namespace engine
{
  class EngineConfig
    {    
    public:
      EngineConfig();
      std::string media_path;
      std::string graph_path;
      std::string ipcType;
      std::string ipcUnixNodePrefix;
      std::string module_path;
      std::string type_path;
      int rendererInterval;
      int netInterval;      
      int port;
    };
}

#endif
