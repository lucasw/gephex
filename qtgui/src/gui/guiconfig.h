#ifndef INCLUDED_GUICONFIG_H
#define INCLUDED_GUICONFIG_H

#include <string>

namespace gui
{  
  struct GuiConfig
  {
    GuiConfig();
    
    std::string media_path;
    std::string ipcType;
    std::string ipcLocator;
    int port;
    std::string engine_binary;
  };
}

#endif
