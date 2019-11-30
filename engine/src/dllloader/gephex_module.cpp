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

#include "gephex_module.h"

#include <cassert>
#include <ctime>
#include <iostream>
#include <stdexcept>

#include "c_input.h"
#include "c_output.h"

#include "c_moduletables.h"
#include "interfaces/itype.h"
#include "interfaces/itypefactory.h"

class UpdateStrategy {
protected:
  int state;

public:
  UpdateStrategy() : state(0) {}
  virtual ~UpdateStrategy(){};
  virtual void dependencies(std::list<std::shared_ptr<IInput>> &l,
                            void *instance,
                            std::vector<IModule::IInputPtr> &inputs,
                            const CModuleVTable &mvt) = 0;

  virtual UpdateStrategy *clone() const = 0;
};

class InputStrategy : public UpdateStrategy {
public:
  InputStrategy() : UpdateStrategy(){};
  void dependencies(std::list<std::shared_ptr<IInput>> &l, void *instance,
                    std::vector<IModule::IInputPtr> &inputs,
                    const CModuleVTable &mvt);

  UpdateStrategy *clone() const { return new InputStrategy(); }
};

class SimpleStrategy : public UpdateStrategy {
public:
  SimpleStrategy() : UpdateStrategy(){};

  void dependencies(std::list<std::shared_ptr<IInput>> &, void *m_instance,
                    std::vector<IModule::IInputPtr> &ins,
                    const CModuleVTable &mvt);

  UpdateStrategy *clone() const { return new SimpleStrategy(); }
};

class DependencyStrategy : public UpdateStrategy {
public:
  DependencyStrategy() : UpdateStrategy(){};

  void dependencies(std::list<std::shared_ptr<IInput>> &, void *m_instance,
                    std::vector<IModule::IInputPtr> &ins,
                    const CModuleVTable &mvt);

  UpdateStrategy *clone() const { return new DependencyStrategy(); }
};

void InputStrategy::dependencies(std::list<std::shared_ptr<IInput>> &, void *,
                                 std::vector<IModule::IInputPtr> &,
                                 const CModuleVTable &) {
  // do nothing because there are no inputs
}

void SimpleStrategy::dependencies(
    std::list<std::shared_ptr<IInput>> &input_list, void *,
    std::vector<IModule::IInputPtr> &inputs, const CModuleVTable &) {
  switch (state) {
  case (0): // tell renderer to render all inputs
    for (auto &input : inputs) {
      input_list.push_back(input);
    }
    state = 1;
    break;
  case (1): // now all data is up-to-date
    for (auto &input : inputs) {
      input->update();
    }
    // doUpdate(instance,inputs,outputs,mvt);
    state = 0;
    break;
  default:
    throw std::runtime_error("Mist");
  }
}

void DependencyStrategy::dependencies(std::list<std::shared_ptr<IInput>> &l,
                                      void *instance,
                                      std::vector<IModule::IInputPtr> &inputs,
                                      const CModuleVTable &mvt) {
  switch (state) {
  case (0): {
    for (auto &input : inputs) {
      if (input->isStrongDependency()) {
        l.push_back(input);
        // std::cout << "strong: pushed " << i << std::endl;
      }
    }
    state = 1;
    break;
  }
  case (1): {
    // update all inputs send by last state
    for (auto &input : inputs) {
      if (input->isStrongDependency()) {
        input->update();
      }
    }

    int *neededInputs = 0;
    mvt.strongDependenciesCalculated(instance, &neededInputs);
    if (neededInputs != 0) {
      for (unsigned int i = 0; i < inputs.size(); ++i) {
        if (!inputs[i]->isStrongDependency() && neededInputs[i] == 1) {
          l.push_back(inputs[i]);
          //  std::cout << "needed: pushed " << i << std::endl;
        }
      }
    }

    // if there are no inputs to be updated we must go to state 0
    // because the runtimesystem will not call dependencies()
    // of the module again this frame
    if (l.empty()) {
      state = 0;
    } else {
      state = 2;
    }
    break;
  }
  case (2): { // update inputs for last state
    int *neededInputs = 0;
    mvt.strongDependenciesCalculated(instance, &neededInputs);
    if (neededInputs != 0) {
      for (unsigned int i = 0; i < inputs.size(); ++i) {
        if (!inputs[i]->isStrongDependency() && neededInputs[i] == 1) {
          inputs[i]->update();
        }
      }
    }
  }
    // doUpdate(instance,inputs,outputs,mvt);
    state = 0;
    break;
  default:
    throw std::runtime_error("Missed");
  }
}

//----------------------------------------------------------------------------

CModule::CModule(void *instance, const CModuleVTable &vtable,
                 const bool is_deterministic,
                 const std::string &module_class_name)
    : IModule(-1), m_instance(instance), m_vtable(&vtable),
      _isDeterministic(is_deterministic), m_module_class_name(module_class_name)

{
#if 0
  std::cout << __FUNCTION__ << " " << m_module_class_name
      << " " << _isDeterministic
      << std::endl;
  std::cout << this << std::endl;
#endif
}

void CModule::init(const CModuleAttributes &attributes,
                   const ITypeFactory &tfactory_,
                   const std::vector<IType *> &defaultInputTypes) {
  m_inputs.resize(attributes.inputs.size());
  m_outputs.resize(attributes.outputs.size());
  for (unsigned int i = 0; i < attributes.inputs.size(); ++i) {
    m_inputs[i] = std::make_shared<CInput>(
        attributes.inputs[i], attributes.isConstInput[i],
        attributes.isStrongDependency[i], shared_from_this(), i, tfactory_,
        attributes.fixedAttributes[i], *defaultInputTypes[i], *m_vtable,
        m_instance);
  }

  for (unsigned int j = 0; j < attributes.outputs.size(); ++j) {
    IType *type = tfactory_.buildNew(attributes.outputs[j]);

    m_outputs[j] =
        std::make_shared<COutput>(shared_from_this(), attributes.outputs[j],
                                  type, j, *m_vtable, m_instance);
  }

  if (attributes.inputs.size() == 0) {
    us = UpdateStrategyPtr(new InputStrategy());
  } else if (m_vtable->strongDependenciesCalculated == 0) {
    us = UpdateStrategyPtr(new SimpleStrategy());
  } else {
    us = UpdateStrategyPtr(new DependencyStrategy());
  }
}

CModule::~CModule() { m_vtable->deleteInstance(m_instance); }

std::string CModule::module_class_name() const { return m_module_class_name; }

const std::vector<CModule::IInputPtr> &CModule::getInputs() { return m_inputs; }

const std::vector<CModule::IOutputPtr> &CModule::getOutputs() {
  return m_outputs;
}

bool CModule::isDeterministic() const { return _isDeterministic; }

std::shared_ptr<IInput> CModule::dependencies() {
  if (m_deps.empty()) {
    us->dependencies(m_deps, m_instance, m_inputs, *m_vtable);
  }

  if (m_deps.empty()) {
    return nullptr;
  }

  auto in = m_deps.front();
  m_deps.pop_front();
  return in;
}

void CModule::update() {
  assert(m_deps.empty());

  if (m_vtable->getPatchLayout != 0) {
    int *out2in;
    // Das patchlayout des Moduls abfragen:
    m_vtable->getPatchLayout(m_instance, &out2in);

    // Alle gepatchten outputs updaten
    for (int i = 0; i < m_outputs.size(); ++i) {
      int patchedInputIndex = out2in[i];
      std::shared_ptr<COutput> out =
          std::static_pointer_cast<COutput>(m_outputs[i]);
      // static_cast<COutput *>(&*outputs[i]);
      assert(out == std::dynamic_pointer_cast<COutput>(m_outputs[i]));

      if (patchedInputIndex != -1) {
        out->setPatchedInput(m_inputs[patchedInputIndex]);
      } else {
        out->unPatch();
      }
    }
  }

  m_vtable->update(m_instance);
}

//----------------------------------------------------------------------------
