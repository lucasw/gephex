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

#ifndef INCLUDED_DLLLOADER_H
#define INCLUDED_DLLLOADER_H

#include <list>
#include <vector>
#include <string>
#include <stdexcept>

#include "interfaces/imoduleclassinfosender.h"
#include "interfaces/imoduleclasssender.h"
#include "interfaces/imoduleclassspecsender.h"
#include "interfaces/itypeclasssender.h"

#include "utils/autoptr.h"
#include "nameresolver.h"

namespace utils 
{
  class SharedLibrary;
  class ILogger;
}

class CTypeClass;
class IModulePlugin; 

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
      /**
       * Create a new dllloader
       *
       * \param logger used for reporting errors
       *
       * \param infoReceiver Receiver for ui specific module data
       * \param specReceiver receiver for typesystem specific module data
       * \param	classReceiver receiver of the loaded modules
       * \param typeClassReceiver receiver of the loaded type plugins
       *
       * \param module_path search loactions for the module plugins
       * \param type_path search loactions for the type plugins
       * \param frei0r_path search loactions for the frei0r plugins
       */
      DllLoader(utils::AutoPtr<utils::ILogger>& logger,
		IModuleClassInfoReceiver& infoReceiver,
		IModuleClassSpecReceiver& specReceiver,
		IModuleClassReceiver& classReceiver,
		ITypeClassReceiver& typeClassReceiver,
		const std::string& module_path,
		const std::string& type_path,
		const std::string& frei0r_path);

      /**
       * Destroy the Dllloader
       * 
       * This unloads all shared libraries and invalidates all loaded plugins
       */
      virtual ~DllLoader();


      /**
       * call this to sent the ui specific module data
       */
      virtual void synchronize();


      // TODO remove these functions from the public interfaces
      // it is not supported to change the receivers after construction
      void registerModuleClassInfoReceiver(IModuleClassInfoReceiver& r)
	{assert(false);}
      void registerModuleClassSpecReceiver(IModuleClassSpecReceiver& r)
	{assert(false);}
      void registerModuleClassReceiver(IModuleClassReceiver& r)
	{assert(false);}
      void registerTypeClassReceiver(ITypeClassReceiver&)
	{assert(false);}
      
    private:
      /** hold shared libraries during lifetime of the object */
      std::list< utils::AutoPtr<utils::SharedLibrary> > m_shared_libraries;

      /** hold types during lifetime of the dllloader */
      std::list< utils::AutoPtr<CTypeClass> > m_gephex_types;
      
      /** hold plugins during lifetime of the dllloader */
      std::list< utils::AutoPtr<IModulePlugin> >
	m_module_plugins;

      /** for unique ids */
      NameResolver resolver;

      IModuleClassInfoReceiver& m_infoReceiver;
      IModuleClassReceiver& m_classReceiver;
      IModuleClassSpecReceiver& m_specReceiver;
      ITypeClassReceiver& m_typeClassReceiver;

      utils::AutoPtr<utils::ILogger> m_logger;

      void processModFile(const std::string&);
      void processFrei0rFile(const std::string&);
      void processTypeFile(const std::string& name);
    };
}

#endif
