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

#ifndef INCLUDED_I_MODULE_PLUGIN_H
#define INCLUDED_I_MODULE_PLUGIN_H

#include <list>

class IModuleClass;

/**
 * This class loads and unloads a frei0r module from a
 * shared library
 */
class IModulePlugin
{
 public:
  /**
   * unload it and deinitialize the plugin
   */
  virtual ~IModulePlugin() {}
    
  /**
   * get the module classes of the plugin
   * \returns a list of pointers to module classes
   */
  virtual std::list<IModuleClass*>& get_module_classes() = 0;
};

#endif
