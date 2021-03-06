/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#include "dllloader.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

// c++ stdlib
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

// helpers
#include "utils/buffer.h"
#include "utils/filesystem.h"
#include "utils/ilogger.h"
#include "utils/sharedlibrary.h"
#include "utils/stringtokenizer.h"
#include "utils/structreader.h"

// for loading type plugins
#include "c_typeclass.h"
#include "c_typetables.h"
#include "gephex_type_plugin.h"
#include "interfaces/itypeclassinforeceiver.h"
#include "interfaces/itypeclassreceiver.h"

// for loading gephex module plugins
#include "gephex_module_class.h"
#include "gephex_module_plugin.h"

// for loading frei0r module plugins
#include "frei0r_module_plugin.h"

// for loading both module plugins
#include "c_moduletables.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"
#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "moduleclassspec.h"
#include "moduleinfoutils.h"

namespace dllloader {

std::vector<std::string> getFilesInPath(const std::string &dirName,
                                        const std::string &ending) {
  std::cout << "load modules from dir: " << dirName << " " << ending << "\n";
  std::vector<std::string> fileNames;

  std::list<utils::DirEntry> entries;
  utils::FileSystem::listDir(dirName, entries);

  for (std::list<utils::DirEntry>::const_iterator it = entries.begin();
       it != entries.end(); ++it) {
    std::string name = it->getName();

    if (name == "." || name == "..")
      continue;

    std::cout << name << "\n";

    if (it->getType() == utils::DirEntry::DIRECTORY) {
      std::vector<std::string> subfiles = getFilesInPath(name, ending);

      fileNames.insert(fileNames.end(), subfiles.begin(), subfiles.end());
    } else {
      if (name.length() > ending.length() &&
          name.substr(name.length() - ending.length(), ending.length()) ==
              ending) {
        fileNames.push_back(dirName + name);
      }
    }
  }

  std::sort(fileNames.begin(), fileNames.end());
  return fileNames;
}

std::vector<std::string> getFilesInPathList(const std::string &pathList,
                                            const std::string &ending) {
  std::vector<std::string> files;

  utils::StringTokenizer st(pathList);
  std::string path;

  while ((path = st.next(";")) != "")
    try {
      std::vector<std::string> fs = getFilesInPath(path, ending);
      files.insert(files.end(), fs.begin(), fs.end());
    } catch (...) {
      // we ignore all paths we cannot open
    }

  return files;
}

std::shared_ptr<utils::SharedLibrary> loadDll(const std::string &filename) {
  try {
    std::shared_ptr<utils::SharedLibrary> sl =
        std::make_shared<utils::SharedLibrary>(filename);
#if (ENGINE_VERBOSITY > 1)
    std::cout << "Loaded Library '" << filename << "'" << std::endl;
#endif
    return sl;
  } catch (std::runtime_error &e) {
    std::ostringstream os;
    os << "loading plugin " << filename
       << " - FAIL (" + std::string(e.what()) + ")";

    std::string msg = os.str();
    std::cerr << msg << std::endl;
    throw std::runtime_error(msg.c_str());
  }
}

extern "C" {
void moduleLog(int level, const char *sender, const char *msg);
};

// TODO: ugly
static std::shared_ptr<utils::ILogger> s_logger(0);

void moduleLog(int level, const char *sender, const char *msg) {
  if (!s_logger)
    return;

  switch (level) {
  case 0:
    s_logger->error(sender, msg);
    break;
  case 1:
    s_logger->warning(sender, msg);
    break;
  default:
    s_logger->log(sender, msg);
  }
}

DllLoader::DllLoader(std::shared_ptr<utils::ILogger> &logger,
                     IModuleClassInfoReceiver &infoReceiver,
                     IModuleClassSpecReceiver &specReceiver,
                     IModuleClassReceiver &classReceiver,
                     ITypeClassReceiver &typeClassReceiver,
                     const std::string &module_path,
                     const std::string &type_path,
                     const std::string &frei0r_path)
    : m_infoReceiver(infoReceiver), m_classReceiver(classReceiver),
      m_specReceiver(specReceiver), m_typeClassReceiver(typeClassReceiver),
      m_logger(logger) {
  s_logger = logger;

#if defined(OS_WIN32)
  const char *MODULE_ENDING = ".dll";
  const char *TYPE_ENDING = ".dll";
#elif defined(OS_POSIX)
  const char *MODULE_ENDING = ".so";
  const char *TYPE_ENDING = ".so";
#else
#error "unknown OS"
#endif

  // load type plugins
  std::vector<std::string> types = getFilesInPathList(type_path, TYPE_ENDING);
  for (std::vector<std::string>::const_iterator it = types.begin();
       it != types.end(); ++it) {
    this->processTypeFile(*it);
  }

  // load module plugins
  std::vector<std::string> modules =
      getFilesInPathList(module_path, MODULE_ENDING);

  for (std::vector<std::string>::const_iterator it = modules.begin();
       it != modules.end(); ++it) {
    this->processModFile(*it);
  }

  // load frei0r plugins
  std::vector<std::string> frei0rs =
      getFilesInPathList(frei0r_path, MODULE_ENDING);

  for (std::vector<std::string>::const_iterator it = frei0rs.begin();
       it != frei0rs.end(); ++it) {
    this->processFrei0rFile(*it);
  }
}

DllLoader::~DllLoader() {
  // TODO
  // 1. call cleanup/deinit methods of all types/effects/plugins
}

void DllLoader::synchronize() {
#if (ENGINE_VERBOSITY > 0)
  std::cout << "sync dllloader" << std::endl;
#endif

  m_infoReceiver.syncStarted();
  // announce all modules
  for (std::list<std::shared_ptr<IModulePlugin>>::iterator it2 =
           m_module_plugins.begin();
       it2 != m_module_plugins.end(); ++it2) {
    for (auto &mc : (*it2)->get_module_classes()) {
      m_infoReceiver.moduleClassLoaded(mc->name(), mc->info());
    }
  }

  m_infoReceiver.syncFinished();
}

void DllLoader::processTypeFile(const std::string &filename) {
  try {
    // load the shared library
    std::shared_ptr<utils::SharedLibrary> shared_library(loadDll(filename));

    // extract the type plugin functions
    const CTypeFunctionTable ft(extract_type_functions(shared_library));
    // create the new type class
    std::shared_ptr<CTypeClass> tc = std::make_shared<CTypeClass>(ft);

    // register the typename and get a unique id
    const int id = resolver.registerObject(tc->getName());

    // hold shared library in memory
    m_shared_libraries.push_back(shared_library);

    m_gephex_types.push_back(tc);

    // distribute the new typeclass to the typefactory
    m_typeClassReceiver.typeClassLoaded(id, *tc);
  } catch (std::runtime_error &e) {
    m_logger->error("processTypeFile", e.what());
  }
}

void DllLoader::processModFile(const std::string &filename) {
  try {
    // load the shared library
    std::shared_ptr<utils::SharedLibrary> sl(loadDll(filename));

    std::shared_ptr<IModulePlugin> plugin =
        std::make_shared<gephex_module_plugin>(*sl, resolver);

    // keep gephex plugin in memory
    m_module_plugins.push_back(plugin);
    // keep the shared library in memory
    m_shared_libraries.push_back(sl);

    auto mcs = plugin->get_module_classes();

    // anounce new modules
    for (auto &mc : mcs) {
      m_infoReceiver.moduleClassLoaded(mc->name(), mc->info());
      m_classReceiver.moduleClassLoaded(mc->name(), *mc);
      m_specReceiver.moduleClassLoaded(mc->name(), mc->spec());
    }

  } catch (std::runtime_error &e) {
    m_logger->error("LoadModuleClass", e.what());
  }
}

void DllLoader::processFrei0rFile(const std::string &fname) {
  try {
    std::shared_ptr<utils::SharedLibrary> sl(loadDll(fname));

    std::shared_ptr<IModulePlugin> plugin =
        std::make_shared<frei0r_module_plugin>(*sl, resolver);

    // keep frei0r plugin in memory
    m_module_plugins.push_back(plugin);
    // keep the shared library in memory
    m_shared_libraries.push_back(sl);

    auto mcs = plugin->get_module_classes();

    // anounce new modules
    for (auto &mc : mcs) {
      m_infoReceiver.moduleClassLoaded(mc->name(), mc->info());
      m_classReceiver.moduleClassLoaded(mc->name(), *mc);
      m_specReceiver.moduleClassLoaded(mc->name(), mc->spec());
    }
  } catch (std::runtime_error &e) {
    std::cerr << e.what();
    m_logger->error("frei0r '" + fname + "'", e.what());
  }
}

} // namespace dllloader
