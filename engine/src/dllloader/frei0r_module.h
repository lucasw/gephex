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

#ifndef INCLUDED_FREI0R_MODULE_H
#define INCLUDED_FREI0R_MODULE_H

#include <vector>

#include "interfaces/imodule.h"

#include "utils/autoptr.h"


class CModuleVTable;
class CModuleAttributes;
class ITypeFactory;
class frei0r_funs_t;

class frei0r_module : public IModule
{
 public:
  typedef utils::AutoPtr<IType> ITypePtr;

public:
  frei0r_module(void* instance,const CModuleVTable&,
		const CModuleAttributes& attributes,const ITypeFactory&,
		const std::vector<IType*>& defaultInputTypes,
		const std::string& module_class_name,
		const frei0r_funs_t& m_frei0r);

  virtual ~frei0r_module();

  std::string module_class_name() const;

  virtual const std::vector<IInputPtr>& getInputs() const;

  virtual const std::vector<IOutputPtr>& getOutputs() const;

  virtual IInput* dependencies();

  virtual void update();

  virtual bool isDeterministic() const;

 private:
  // not implemented
  frei0r_module(const frei0r_module&);
  const frei0r_module& operator=(const frei0r_module&);
  
  void* m_instance;
  const CModuleVTable* m_vtable;
  const frei0r_funs_t& m_frei0r;
  
  std::vector<IInputPtr> inputs;
  std::vector<IOutputPtr> outputs;

  bool _isDeterministic;

  std::list<IInput*> m_deps;

  std::string m_module_class_name;

  void doUpdate();
};


#endif

