/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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

#ifndef INCLUDED_DLLLOADER_H
#define INCLUDED_DLLLOADER_H

#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "interfaces/imoduleclassloadercontrolreceiver.h"
#include "interfaces/imoduleclassinfosender.h"
#include "interfaces/imoduleclasssender.h"
#include "interfaces/imoduleclassspecsender.h"
#include "interfaces/imoduleclassnamesender.h"

#include "interfaces/itypeclassloadercontrolreceiver.h"
#include "interfaces/itypeclassinfosender.h"
#include "interfaces/itypeclasssender.h"
#include "interfaces/itypeclassnamesender.h"

#include "utils/autoptr.h"

struct frei0r_funs_t;

namespace utils 
{
  class Buffer;
  class SharedLibrary;
  class ILogger;
}

class NameResolver;
class CTypeFunctionTable;
class CModuleFunctionTable;

namespace dllloader
{

  /**
   * Die Klasse Dllloader kuemmert sich um das dynamische Nachladen
   * von Typ und Modul dlls.
   */
  class DllLoader: 
    public IModuleClassLoaderControlReceiver,
    public ITypeClassLoaderControlReceiver,
    public IModuleClassInfoSender, 
    public IModuleClassSpecSender, 
    public IModuleClassSender, 
    public ITypeClassInfoSender, 
    public ITypeClassSender,
    public IModuleClassNameSender,
    public ITypeClassNameSender
    {

    public:
      typedef utils::AutoPtr<utils::SharedLibrary> SharedLibraryPtr;


      /**
       * Erzeugt neuen DllLoader.
       * @param logger used for reporting errors
       */
      DllLoader(utils::AutoPtr<utils::ILogger>& logger);

      virtual ~DllLoader();

      /**
       * Liest und verarbeitet die module und die typ dateien.
       * Davor sollte der ModuleClassNameReceiver registriert sein !!
       */
      void readDlls(const std::vector<std::string>& modules,
		    const std::vector<std::string>& types,
		    const std::vector<std::string>& frei0rs);

      virtual void loadModuleClass(const std::string& name);
      virtual void loadFrei0r(frei0r_funs_t&, SharedLibraryPtr sl,
			      const std::string moduleName);
      virtual void unloadModuleClass(const std::string& name);

      //TODO: war mal const
      virtual void synchronize();

      /**
       * Unloads all module and type dlls. Should be called before
       * the listeners are destroyed.
       */
      void unloadAll();
  
      virtual void registerModuleClassInfoReceiver(IModuleClassInfoReceiver&);
      virtual void registerModuleClassSpecReceiver(IModuleClassSpecReceiver&);
      virtual void registerModuleClassReceiver(IModuleClassReceiver&);
      virtual void registerModuleClassNameReceiver(IModuleClassNameReceiver&);

      virtual void loadTypeClass(const std::string& name);
      virtual void unloadTypeClass(const std::string& name);
      virtual void registerTypeClassInfoReceiver(ITypeClassInfoReceiver&);
      virtual void registerTypeClassReceiver(ITypeClassReceiver&);
      virtual void registerTypeClassNameReceiver(ITypeClassNameReceiver&);

    private:
      SharedLibraryPtr loadDll(const std::string& filename);
      std::string getDllName(const std::string& filename);

      void loadModule(SharedLibraryPtr,
                      const std::string& moduleName);

      void processModFile(const std::string&);
      void processFrei0rFile(const std::string&);
      void processTypFile(const std::string&);
	
      void constructModuleClass(CModuleFunctionTable* fTable,
				SharedLibraryPtr sl,
                                const std::string& moduleName,
				frei0r_funs_t*);

      NameResolver* resolver;

      IModuleClassInfoReceiver* m_infoReceiver;
      IModuleClassReceiver* m_classReceiver;
      IModuleClassSpecReceiver* m_specReceiver;
      IModuleClassNameReceiver* m_nameReceiver;

      ITypeClassInfoReceiver* m_typeInfoReceiver;
      ITypeClassReceiver* m_typeClassReceiver;
      ITypeClassNameReceiver* m_typeNameReceiver;

      std::map<std::string,std::string> m_mod2fileName;
      std::map<std::string,std::string> m_typ2fileName;
      std::map<std::string,std::string> m_f0r2fileName;

      std::map<std::string,SharedLibraryPtr> m_moduleHandles;
      std::map<std::string,utils::AutoPtr<utils::Buffer> > m_moduleInfos;

      //std::map<std::string,SharedLibraryPtr> m_typeHandles;

      utils::AutoPtr<utils::ILogger> m_logger;
    };

}

#endif
