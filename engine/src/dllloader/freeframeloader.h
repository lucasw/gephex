#ifndef INCLUDED_FREEFRAME_LOADER_H
#define INCLUDED_FREEFRAME_LOADER_H

#include <string>

namespace utils
{
  class SharedLibrary;
  class ILogger;
}

class MetaModule;

namespace dllloader {

class FreeFrameLoader
{
 public:
  static MetaModule* loadPlugin(const utils::SharedLibrary& sl,
                                utils::ILogger& logger);
};

}
#endif
