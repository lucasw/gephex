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

#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

// c++ stdlib
#include <cassert>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

// helpers
#include "utils/structreader.h"
#include "utils/buffer.h"
#include "utils/autoptr.h"
#include "utils/sharedlibrary.h"
#include "utils/ilogger.h"
#include "utils/filesystem.h"
#include "utils/stringtokenizer.h"

// for loading type plugins 
#include "gephex_type_plugin.h"
#include "c_typetables.h"
#include "c_typeclass.h"
#include "interfaces/itypeclassreceiver.h"
#include "interfaces/itypeclassinforeceiver.h"

// for loading gephex module plugins
#include "gephex_module_class.h"
#include "gephex_module_plugin.h"

// for loading frei0r module plugins
#include "frei0r_module_plugin.h"

// for loading both module plugins
#include "c_moduletables.h"
#include "moduleinfoutils.h" 
#include "moduleclassspec.h" 
#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"

namespace dllloader
{

  std::vector<std::string> getFilesInPath(const std::string& dirName,
                                          const std::string& ending)
  {
    std::vector<std::string> fileNames;
    
    std::list<utils::DirEntry> entries;
    utils::FileSystem::listDir(dirName, entries);
    
    for (std::list<utils::DirEntry>::const_iterator it = entries.begin();
         it != entries.end(); ++it)
      {
        std::string name = it->getName();

        if (name == "." || name == "..")
          continue;
      
        if (it->getType() == utils::DirEntry::DIRECTORY)
          {
            std::vector<std::string> 
              subfiles= getFilesInPath(name, ending);

            fileNames.insert(fileNames.end(),
                             subfiles.begin(), subfiles.end());
          }
        else
          {
            if (name.length() > ending.length() 
                && name.substr(name.length()-ending.length(),
                               ending.length()) == ending)
              {
                fileNames.push_back(dirName + name);
              }
          }
      }
    return fileNames;
  }

  std::vector<std::string> getFilesInPathList(const std::string& pathList,
					      const std::string& ending)
  {
    std::vector<std::string> files;

    utils::StringTokenizer st(pathList);
    std::string path;

    while ((path = st.next(";")) != "")
    try
      {
        std::vector<std::string> fs = getFilesInPath(path, ending);
        files.insert(files.end(),fs.begin(), fs.end());
      }
    catch (...)
      {
        // we ignore all paths we cannot open
      }

    return files;
  }

  utils::AutoPtr<utils::SharedLibrary> loadDll(const std::string& filename)
  {
    try {
      utils::AutoPtr<utils::SharedLibrary> sl(new utils::SharedLibrary(filename));
#if (ENGINE_VERBOSITY > 1)
      std::cout << "Loaded Library '" << filename << "'" << std::endl;
#endif
      return sl;
    }
    catch (std::runtime_error& e) {
      std::ostringstream os;
      os << "loading plugin " << filename << " - FAIL (" 
	+ std::string(e.what()) + ")";

      std::string msg = os.str();
      std::cerr << msg << std::endl;
      throw std::runtime_error(msg.c_str());
    }
  }


    extern "C" 
  {
    void moduleLog(int level, const char* sender, const char* msg);
  };


  //TODO: ugly
  static utils::AutoPtr<utils::ILogger> s_logger(0);

  void moduleLog(int level, const char* sender, const char* msg)
  {
    if (!s_logger)
      return;

    switch(level)
      {
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




  DllLoader::DllLoader(utils::AutoPtr<utils::ILogger>& logger,
		       IModuleClassInfoReceiver& infoReceiver,
		       IModuleClassSpecReceiver& specReceiver,
		       IModuleClassReceiver& classReceiver,
		       ITypeClassReceiver& typeClassReceiver,
		       const std::string& module_path,
		       const std::string& type_path,
		       const std::string& frei0r_path
		       )
    : m_infoReceiver(infoReceiver),
      m_classReceiver(classReceiver),
      m_specReceiver(specReceiver),
      m_typeClassReceiver(typeClassReceiver), m_logger(logger)
  {
    s_logger = logger;

#if defined(OS_WIN32)
    const char* MODULE_ENDING = ".dll";
    const char* TYPE_ENDING   = ".dll";
#elif defined(OS_POSIX)
    const char* MODULE_ENDING = ".so";
    const char* TYPE_ENDING   = ".so";
#else
#error "unknown OS"
#endif
    
    // load type plugins
    std::vector<std::string> types = getFilesInPathList(type_path,
                                                        TYPE_ENDING);
    for(std::vector<std::string>::const_iterator it =types.begin();
	it != types.end();
	++it)
      {
	this->processTypeFile(*it);
      }
    
    // load module plugins
    std::vector<std::string> modules = getFilesInPathList(module_path,
                                                          MODULE_ENDING);

    for (std::vector<std::string>::const_iterator it = modules.begin();
	 it != modules.end();
	 ++it)
      {	
	this->processModFile(*it);
      }

    // load frei0r plugins
    std::vector<std::string> frei0rs = getFilesInPathList(frei0r_path,
							  MODULE_ENDING);

    for (std::vector<std::string>::const_iterator it = frei0rs.begin();
	 it != frei0rs.end();
	 ++it)
      {	
	this->processFrei0rFile(*it);
      }
  }
	
  DllLoader::~DllLoader()
  {
    // TODO
    // 1. call cleanup/deinit methods of all types/effects/plugins
  }

  

	
  void DllLoader::synchronize()
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "sync dllloader" << std::endl;
#endif

    m_infoReceiver.syncStarted();
    // announce all modules
    for (std::list<utils::AutoPtr<IModulePlugin> >::iterator it2
	   = m_module_plugins.begin();
	 it2 != m_module_plugins.end();
	 ++it2)
      {
	for (std::list<IModuleClass*>::iterator it
	       = (*it2)->get_module_classes().begin();
	     it != (*it2)->get_module_classes().end(); ++ it)
	  {
	    m_infoReceiver.moduleClassLoaded(  (*it)->name(),(*it)->info()  );
	  }
      }
    
    m_infoReceiver.syncFinished();
  }
	
  void DllLoader::processTypeFile(const std::string& filename)
  {
    try 
      {
	// load the shared library
	utils::AutoPtr<utils::SharedLibrary>
	  shared_library( loadDll(filename) );

	// extract the type plugin functions
	const CTypeFunctionTable ft( extract_type_functions( shared_library ) );
	// create the new type class
	utils::AutoPtr<CTypeClass> tc (new CTypeClass(ft) );

	// register the typename and get a unique id
	const int id = resolver.registerObject(tc->getName());
	
	// hold shared library in memory
	m_shared_libraries.push_back(shared_library);

	m_gephex_types.push_back(tc);
	
	// distribute the new typeclass to the typefactory
	m_typeClassReceiver.typeClassLoaded(id, *tc);
      }
    catch (std::runtime_error& e)
      {
	m_logger->error("processTypeFile", e.what());
      }
  }
	

  void DllLoader::processModFile(const std::string& filename)
  {
    try 
      {
	// load the shared library
	utils::AutoPtr<utils::SharedLibrary>
	  sl( loadDll(filename) );

	utils::AutoPtr<IModulePlugin> plugin
	  (new gephex_module_plugin(*sl, resolver));

	// keep gephex plugin in memory
	m_module_plugins.push_back(plugin);
	// keep the shared library in memory
	m_shared_libraries.push_back(sl);

	std::list<IModuleClass*> mcs= plugin->get_module_classes();

	// anounce new modules
	for (std::list<IModuleClass*>::iterator it= mcs.begin();
	     it != mcs.end(); ++ it)
	  {
	    m_infoReceiver.moduleClassLoaded(  (*it)->name(),(*it)->info()  );
	    m_classReceiver.moduleClassLoaded( (*it)->name(), (*(*it))      );
	    m_specReceiver.moduleClassLoaded(  (*it)->name(),  (*it)->spec() );
	  }
	
      }
    catch (std::runtime_error& e)
      {
	m_logger->error("LoadModuleClass", e.what());
      }
  }



  void DllLoader::processFrei0rFile(const std::string& fname)
  {
    try 
      {
	utils::AutoPtr<utils::SharedLibrary> sl ( loadDll(fname) );

	utils::AutoPtr<IModulePlugin> plugin
	  (new frei0r_module_plugin(*sl, resolver));

	// keep frei0r plugin in memory
	m_module_plugins.push_back(plugin);
	// keep the shared library in memory
	m_shared_libraries.push_back(sl);

	std::list<IModuleClass*> mcs= plugin->get_module_classes();

	// anounce new modules
	for (std::list<IModuleClass*>::iterator it= mcs.begin();
	     it != mcs.end(); ++ it)
	  {
	    m_infoReceiver.moduleClassLoaded(  (*it)->name(),(*it)->info()  );
	    m_classReceiver.moduleClassLoaded( (*it)->name(), (*(*it))      );
	    m_specReceiver.moduleClassLoaded(  (*it)->name(),  (*it)->spec() );
	  }
      }
    catch (std::runtime_error& e)
      {
	std::cerr << e.what();
	m_logger->error("frei0r", e.what());
      }
  }





}
