#ifndef INCLUDED_ENGINECONFIG_H
#define INCLUDED_ENGINECONFIG_H

#include <string>
#include "structreader.h"

namespace engine
{
  class EngineConfig
    {    
    public:
      EngineConfig();
      utils::StructReader sr;
      std::string graphDir;      
      std::string ipcType;
      std::string ipcUnixNodePrefix;
      std::string moduleDirs;
      std::string typeDirs;
      int rendererInterval;
      int netInterval;      
      int port;
    private:
      utils::StructReader readConfigFile();
    };
}

#endif
