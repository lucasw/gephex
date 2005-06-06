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
#include <cassert>

#include "interfaces/imoduleclassinfosender.h"
#include "interfaces/imoduleclasssender.h"
#include "interfaces/imoduleclassspecsender.h"

#include "interfaces/itypeclasssender.h"

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
    public IModuleClassInfoSender, 
    public IModuleClassSpecSender, 
    public IModuleClassSender, 
    public ITypeClassSender
    {

    public:
      typedef utils::AutoPtr<utils::SharedLibrary> SharedLibraryPtr;


      /**
       * Erzeugt neuen DllLoader.
       * @param logger used for reporting errors
       */
      DllLoader(utils::AutoPtr<utils::ILogger>& logger,
		IModuleClassInfoReceiver&,
		IModuleClassSpecReceiver&,
		IModuleClassReceiver&,
		ITypeClassReceiver&,
		const std::string& module_path,
		const std::string& type_path,
		const std::string& frei0r_path);

      virtual ~DllLoader();


      /**
       * call this on connect of ModuleClassInfoReceiver
       */
      virtual void synchronize();


      // TODO remove these functions from the public interfaces
      void registerModuleClassInfoReceiver(IModuleClassInfoReceiver& r)
	{assert(false);}
      void registerModuleClassSpecReceiver(IModuleClassSpecReceiver& r)
	{assert(false);}
      void registerModuleClassReceiver(IModuleClassReceiver& r)
	{assert(false);}
      void registerTypeClassReceiver(ITypeClassReceiver&)
	{assert(false);}
      
    private:
      /**
       * Liest und verarbeitet die module und die typ dateien.
       */
      void readDlls(const std::vector<std::string>& modules,
		    const std::vector<std::string>& types,
		    const std::vector<std::string>& frei0rs);

      
      SharedLibraryPtr loadDll(const std::string& filename);
      std::string getDllName(const std::string& filename);

      void loadFrei0r(frei0r_funs_t&, SharedLibraryPtr sl,
			      const std::string moduleName);

      void loadModule(SharedLibraryPtr,
                      const std::string& moduleName);

      void processModFile(const std::string&);
      void processFrei0rFile(const std::string&);
      void processTypeFile(const std::string& name);

      
      void constructModuleClass(CModuleFunctionTable* fTable,
				SharedLibraryPtr sl,
                                const std::string& moduleName,
				frei0r_funs_t*);

      NameResolver* resolver;

      IModuleClassInfoReceiver& m_infoReceiver;
      IModuleClassReceiver& m_classReceiver;
      IModuleClassSpecReceiver& m_specReceiver;
      ITypeClassReceiver& m_typeClassReceiver;

      std::map<std::string,std::string> m_mod2fileName;
      std::map<std::string,std::string> m_typ2fileName;
      std::map<std::string,std::string> m_f0r2fileName;

      std::map<std::string,SharedLibraryPtr> m_moduleHandles;
      std::map<std::string,utils::AutoPtr<utils::Buffer> > m_moduleInfos;

      utils::AutoPtr<utils::ILogger> m_logger;
    };
}

#endif
