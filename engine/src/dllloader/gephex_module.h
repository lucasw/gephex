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

#include <memory>
#include <vector>

#include "interfaces/imodule.h"

class CModuleVTable;
class CModuleAttributes;
class UpdateStrategy;
class ITypeFactory;

class CModule : public IModule, public std::enable_shared_from_this<CModule> {
public:
  typedef std::shared_ptr<IType> ITypePtr;

public:
  CModule(void *instance, const CModuleVTable &, const bool is_deterministic,
          const std::string &module_class_name);

  virtual ~CModule();

  void init(const CModuleAttributes &attributes, const ITypeFactory &tfactory_,
            const std::vector<IType *> &defaultInputTypes);

  std::string module_class_name() const;

  virtual const std::vector<IInputPtr> &getInputs();

  virtual const std::vector<IOutputPtr> &getOutputs();

  virtual std::shared_ptr<IInput> dependencies();

  virtual void update();

  virtual bool isDeterministic() const;

  // void setData(const IInput*/*,const IType**/);

private:
  void *m_instance;
  const CModuleVTable *m_vtable;

  std::vector<IInputPtr> m_inputs;
  std::vector<IOutputPtr> m_outputs;

  bool _isDeterministic;
  typedef std::shared_ptr<UpdateStrategy> UpdateStrategyPtr;
  UpdateStrategyPtr us;

  std::list<std::shared_ptr<IInput>> m_deps;

  std::string m_module_class_name;

  // CModule(const CModule&);

  const CModule &operator=(const CModule &); // nicht impl.

  void doUpdate();
};

#endif
