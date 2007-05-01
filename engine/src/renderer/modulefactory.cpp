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

#include "modulefactory.h"
//#include "imodule.h"
#include "interfaces/imoduleclass.h"

#include <stdexcept>

namespace renderer
{

  ModuleFactory::ModuleFactory() : moduleClasses()
  {
  }

  ModuleFactory::~ModuleFactory()
  {
  }

  IModule* ModuleFactory::buildNewModule(const std::string& name,
					 const ITypeFactory& tFactory) const
  {
    ClassMap::const_iterator i = moduleClasses.find(name);
    if (i == moduleClasses.end())
      {
	throw std::runtime_error("Ungültige Modulklassen ID");
      }

    return i->second->buildInstance(tFactory);
    //irgendwo muss man die nopch herholen
    // oder in jedem IModule speichern :)
  }


  void ModuleFactory::registerModuleClass(const std::string& name,
					  const IModuleClass& moduleClass)
  {
    ClassMap::const_iterator i = moduleClasses.find(name);
    if (i != moduleClasses.end())
      {
	throw std::runtime_error("Modul ID existiert bereits bei "
				 "ModuleFactory::registerModuleClass()");
      }
	
    moduleClasses[name] = &moduleClass;
  }

  void ModuleFactory::unregisterModuleClass(const std::string& name)
  {
    ClassMap::iterator i = moduleClasses.find(name);
    if (i == moduleClasses.end())
      {
	throw std::runtime_error("Modul ID existiert nicht bei "
				 "ModuleFactory::unregisterModuleClass()");
      }

    moduleClasses.erase(i);
  }

  /*  std::list<std::string> ModuleFactory::getAllNames() const
  {
    std::list<std::string> liste;
    for (ClassMap::const_iterator i = moduleClasses.begin();
	 i != moduleClasses.end(); ++i)
      {
	liste.push_back(i->first);
      }
	
    return liste;
    }*/

} // end of namespace
