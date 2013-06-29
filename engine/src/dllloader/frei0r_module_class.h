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

#ifndef INCLUDED_FREI0R_MODULE_CLASS_H
#define INCLUDED_FREI0R_MODULE_CLASS_H

#include "interfaces/imoduleclass.h"

#include "c_moduletables.h"
#include "utils/autoptr.h"
#include "utils/buffer.h"
#include "moduleclassspec.h"
#include "frei0r_module_plugin.h"

class CModuleFunctionTable;
class CModuleAttributes;
class IType;
class NameResolver;


class CModuleFunctionTable;

extern "C"
{
#include "frei0r.h"
}

  typedef int  (*f0r_init_t)();
  typedef void (*f0r_deinit_t)();
  typedef void (*f0r_get_plugin_info_t)(f0r_plugin_info_t* info);
  typedef void (*f0r_get_param_info_t)(f0r_param_info_t* info,
				       int param_index);
  typedef f0r_instance_t (*f0r_construct_t)(int width, int height);
  typedef void (*f0r_destruct_t)(f0r_instance_t instance);

  typedef void (*f0r_set_param_value_t)(f0r_instance_t instance, 
				      f0r_param_t param, int param_index);

  typedef void (*f0r_get_param_value_t)(f0r_instance_t instance,
				      f0r_param_t param, int param_index);

  typedef void (*f0r_update_t)(f0r_instance_t isntance, double time,
			       const uint32_t* inframe, uint32_t* outframe);

  typedef void (*f0r_update2_t)(f0r_instance_t isntance, double time,
				const uint32_t* inframe1,
				const uint32_t* inframe2,
				const uint32_t* inframe3,
				uint32_t* outframe);

  struct frei0r_funs_t
  {
    f0r_init_t            init;
    f0r_deinit_t          deinit;
    f0r_get_plugin_info_t get_plugin_info;
    f0r_get_param_info_t  get_param_info;
    f0r_construct_t       construct;
    f0r_destruct_t        destruct;
    f0r_set_param_value_t set_param_value;
    f0r_get_param_value_t  get_param_value;
    f0r_update_t          update;
    f0r_update2_t          update2;
  };



class Frei0rModuleClass : public IModuleClass
{
 public:
  /**
   * create a frei0r module factory from a struct of
   * functions.
   * \param ft the functionpointers in this struct must be valid during
   *           lifetime of the Frei0rModuleClass object.
   * \param resolver is needed for check the uniqueness of the ids
   */
  Frei0rModuleClass(const frei0r_funs_t& ft,
		    NameResolver& resolver);

  /**
   * \returns the name of the frei0r module class
   */
  const std::string& name() const;

  /**
   * \returns the module class info string for the ui
   */
  virtual const utils::Buffer& info() const;
  
  /**
   * \ returns the signature spec of the module class
   */
  virtual const ModuleClassSpec& spec() const;
  

  /**
   * Create a frei0r module.
   * \returns a new frei0r module. The caller is responsible for this object
   * \param tFactory this factory is needed to set the default values
   *                 of the inputs
   */
  virtual IModule* buildInstance(const ITypeFactory& tFactory) const;

  /**
   * call deinit functions of the frei0r plugin
   */
  virtual ~Frei0rModuleClass();
 private:
  Frei0rModuleClass& operator=(const Frei0rModuleClass&); // not implemented
  Frei0rModuleClass(const Frei0rModuleClass&); // not implemented

  const frei0r_funs_t m_frei0r;
  
  CModuleFunctionTable m_functionTable;
  CModuleAttributes m_attributes;
  mutable std::vector<IType*> m_defaultInputValues;
  std::string m_name;
  int m_frei0r_plugin_type;
  utils::Buffer m_info;
  utils::AutoPtr<ModuleClassSpec> m_spec;
};

#endif
