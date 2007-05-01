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

#include "frei0r_module_plugin.h"

#include <stdexcept>

#include "frei0r_module_class.h"
#include "utils/sharedlibrary.h"

frei0r_module_plugin::frei0r_module_plugin(utils::SharedLibrary& sl,
					   NameResolver& resolver)
{
  frei0r_funs_t ft;
  
  ft.init            = (f0r_init_t) sl.loadSymbol("f0r_init");
  ft.deinit          = (f0r_deinit_t) sl.loadSymbol("f0r_deinit");
  ft.get_plugin_info = (f0r_get_plugin_info_t) 
    sl.loadSymbol("f0r_get_plugin_info");
  ft.get_param_info  = (f0r_get_param_info_t)
    sl.loadSymbol("f0r_get_param_info");
  ft.construct       = (f0r_construct_t) sl.loadSymbol("f0r_construct");
  ft.destruct        = (f0r_destruct_t) sl.loadSymbol("f0r_destruct");
  ft.set_param_value = (f0r_set_param_value_t) sl.loadSymbol("f0r_set_param_value");
  ft.get_param_value = (f0r_get_param_value_t)
    sl.loadSymbol("f0r_get_param_value");
  ft.update          = (f0r_update_t) sl.loadSymbol("f0r_update");
  ft.update2         = (f0r_update2_t) sl.loadSymbol("f0r_update2");
  
  if (ft.init == 0 || ft.deinit == 0 || ft.get_plugin_info == 0 ||
      ft.get_param_info == 0 || ft.construct == 0 || ft.destruct == 0 ||
      ft.set_param_value == 0 || ft.get_param_value == 0 ||
      (ft.update == 0&&ft.update2 == 0))
    {
      throw std::runtime_error("some symbols are missing in frei0r plugin");
    }

  IModuleClass* mc = new Frei0rModuleClass(ft, resolver);

  m_module_classes.push_back(mc);
}
  

frei0r_module_plugin::~frei0r_module_plugin()
{
}


std::list<IModuleClass*>& frei0r_module_plugin::get_module_classes()
{
  return m_module_classes;
}
