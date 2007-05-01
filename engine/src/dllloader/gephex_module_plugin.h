/* This source file is a part of the GePhex Project.

 Copyright (C) 2005

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

#ifndef INCLUDED_GEPHEX_MODULE_PLUGIN_H
#define INCLUDED_GEPHEX_MODULE_PLUGIN_H

#include "interfaces/imoduleplugin.h"

#include <list>

class NameResolver;
class IModuleClass;

namespace utils
{
  class SharedLibrary;
}


/**
 * This class loads and unloads a frei0r module from a
 * shared library
 */
class gephex_module_plugin : public IModulePlugin
{
 public:
  /**
   * load the gephex module plugin and initialize it
   * \param sl The shared library must the valid during the plugin lifetime
   */
  gephex_module_plugin(utils::SharedLibrary& sl,
		       NameResolver& resolver);
  
  /**
   * unload it and deinitialize the gephex module plugin
   */
  ~gephex_module_plugin(); 
  /**
   * get the module classes of the gephex module plugin
   * \returns a list of pointers to module classes
   */
  std::list<IModuleClass*>& get_module_classes();
 private:
  // not implemented
  gephex_module_plugin(const gephex_module_plugin&);
  gephex_module_plugin& operator=(const gephex_module_plugin&);

  // stores the module classes of the plugin
  std::list< IModuleClass* > m_module_classes;
};

#endif

