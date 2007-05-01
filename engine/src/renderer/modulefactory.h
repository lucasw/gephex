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

#ifndef INCLUDED_MODULEFACTORY_H
#define INCLUDED_MODULEFACTORY_H

#include <list>
#include <map>
#include <string>

#include "utils/autoptr.h"

class IModule;
class IModuleClass;
class ITypeFactory;

namespace renderer
{

class IModuleFactory
{
public:
  virtual IModule* buildNewModule(const std::string& className,
				  const ITypeFactory&) const = 0;

};

class ModuleRegistry
{
public:
  virtual void registerModuleClass(const std::string& classNme,
				   const IModuleClass& moduleClass) = 0;

  virtual void unregisterModuleClass(const std::string& classNme) = 0;
};

class ModuleFactory : public IModuleFactory, public ModuleRegistry//TODO
{
public:
  ModuleFactory();
  virtual ~ModuleFactory();
  virtual IModule* buildNewModule(const std::string& className,
				  const ITypeFactory&) const;

  virtual void registerModuleClass(const std::string& className,
				   const IModuleClass& moduleClass);

  virtual void unregisterModuleClass(const std::string& classNme);

  //  virtual std::list<std::string> getAllNames() const;// todo

private:
  typedef std::map<const std::string, const IModuleClass* > ClassMap;
  ClassMap moduleClasses;
};

} // end of namespace

#endif
