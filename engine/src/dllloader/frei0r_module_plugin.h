/* This source file is a part of the GePhex Project.

 Copyright (C) 2004-2005

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

#ifndef INCLUDED_FREI0R_MODULE_PLUGIN_H
#define INCLUDED_FREI0R_MODULE_PLUGIN_H

#include <list>

#include "interfaces/imoduleplugin.h"

namespace utils
{
  class SharedLibrary;
}

class NameResolver;
class IModuleClass;

/**
 * This class loads and unloads a frei0r module from a
 * shared library
 */
class frei0r_module_plugin : public IModulePlugin
{
 public:
  /**
   * load the frei0r plugin and initialize it
   * \param sl The shared library must the valid during the plugin lifetime
   */
  frei0r_module_plugin(utils::SharedLibrary& sl,
		       NameResolver& resolver);
  
  /**
   * unload it and deinitialize the frei0r plugin
   */
  ~frei0r_module_plugin(); 
  /**
   * get the module classes of the frei0r plugin
   * \returns a list of pointers to module classes
   */
  std::list<IModuleClass*>& get_module_classes();
 private:
  // not implemented
  frei0r_module_plugin(const frei0r_module_plugin&);
  frei0r_module_plugin& operator=(const frei0r_module_plugin&);

  // stores the module classes of the plugin
  std::list< IModuleClass* > m_module_classes;
};

#endif

