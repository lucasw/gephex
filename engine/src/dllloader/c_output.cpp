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

#include "c_output.h"
#include "c_outputplug.h"

#include "interfaces/itype.h"

#include "c_moduletables.h"

COutput::COutput(std::shared_ptr<IModule> mod, int _typeID, IType *_data,
                 int index, const COutputVTable &vtable, void *instance)
    : m_module(mod), /*isChanged(true),*/ m_typeID(_typeID), m_plugs(),
      m_data(_data), m_patchedInput(0), m_index(index), m_vtable(&vtable),
      m_instance(instance) {
  m_vtable->setOutput(m_instance, m_index, m_data->getPointer());
}

COutput::~COutput() { delete m_data; }

/*void COutput::setData(const IType* _data) //TODO: remove?
{
        data = _data;
        for (PlugList::iterator i = plugs.begin();
             i != plugs.end(); ++i)
          {
            (*i)->setData(_data);
            }
        //TODO set data of all outputplugs and copy if needed
}*/

std::shared_ptr<IModule> COutput::getModule() const { return m_module; }

std::shared_ptr<IOutputPlug> COutput::plugIn(std::shared_ptr<IInput> in) {
  auto plug = std::make_shared<COutputPlug>(shared_from_this(), in);
  m_plugs.push_back(plug);
  plug->setData(m_data);
  return plug;
}

void COutput::unPlug(std::shared_ptr<IInput> in) {
  for (PlugList::iterator it = m_plugs.begin(); it != m_plugs.end(); ++it) {
    IOutputPlugPtr current = *it;
    if (current->getInput() == in) {
      m_plugs.erase(it);
      break;
    }
  }
}

int COutput::getType() const { return m_typeID; }

std::list<std::shared_ptr<IInput>> COutput::getConnectedInputs() const {
  std::list<std::shared_ptr<IInput>> inputs;

  for (auto &plug : m_plugs) {
    inputs.push_back(plug->getInput());
  }

  return inputs;
}

std::shared_ptr<IInput> COutput::getPatchedInput() const {
  return m_patchedInput;
}

void COutput::setPatchedInput(std::shared_ptr<IInput> in) {
  m_patchedInput = in;
  for (PlugList::iterator it = m_plugs.begin(); it != m_plugs.end(); ++it) {
    (*it)->setData(in->getData());
  }

  m_vtable->setOutput(m_instance, m_index, in->getData()->getPointer());
}

void COutput::unPatch() {
  if (m_patchedInput) {
    m_patchedInput = nullptr;
    for (PlugList::iterator it = m_plugs.begin(); it != m_plugs.end(); ++it) {
      (*it)->setData(m_data);
    }
  }
  m_vtable->setOutput(m_instance, m_index, m_data->getPointer());
}
