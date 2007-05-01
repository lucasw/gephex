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

#ifndef INCLUDED_GEPHEX_MODULE_H
#define INCLUDED_GEPHEX_MODULE_H

#include <vector>

#include "interfaces/imodule.h"

#include "utils/autoptr.h"

class CModuleVTable;
class CModuleAttributes;
class UpdateStrategy;
class ITypeFactory;

class CModule : public IModule
{
 public:
  typedef utils::AutoPtr<IType> ITypePtr;

public:
  CModule(void* instance,const CModuleVTable&,
	  const CModuleAttributes& attributes,const ITypeFactory&,
	  const std::vector<IType*>& defaultInputTypes,
	  const std::string& module_class_name);

  virtual ~CModule();

  std::string module_class_name() const;

  virtual const std::vector<IInputPtr>& getInputs() const;

  virtual const std::vector<IOutputPtr>& getOutputs() const;

  virtual IInput* dependencies();

  virtual void update();

  virtual bool isDeterministic() const;

  //void setData(const IInput*/*,const IType**/);

private:

  void* m_instance;
  const CModuleVTable* m_vtable;

  std::vector<IInputPtr> inputs;
  std::vector<IOutputPtr> outputs;

  bool _isDeterministic;
  typedef utils::AutoPtr<UpdateStrategy> UpdateStrategyPtr;
  UpdateStrategyPtr us;

  std::list<IInput*> m_deps;

  std::string m_module_class_name;

  //CModule(const CModule&);

  const CModule& operator=(const CModule&); // nicht impl.

  void doUpdate();

};


#endif

