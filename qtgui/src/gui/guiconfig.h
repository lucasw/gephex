#ifndef INCLUDED_GUICONFIG_H
#define INCLUDED_GUICONFIG_H

#include <string>

#include "utils/structreader.h"
#include "utils/autoptr.h"

namespace gui
{

  typedef utils::AutoPtr<utils::StructReader> StructReaderPtr;

  struct GuiConfig
  {
    std::string ipcType;
    std::string ipcLocator;
    int port;
    StructReaderPtr sr;
  };

  GuiConfig createGuiConfig();
}

#endif
