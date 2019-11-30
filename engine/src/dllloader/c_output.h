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

#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H

#include <list>
#include <memory>

#include "interfaces/imodule.h"

class COutputPlug;

class COutputVTable;

class COutput : public IOutput, public std::enable_shared_from_this<COutput> {
public:
  COutput(std::shared_ptr<IModule> mod, int _typeID, IType *data, int index,
          const COutputVTable &vtable, void *instance);
  virtual ~COutput();

  // virtual void setData(const IType* data); //TODO: remove?

  virtual std::shared_ptr<IModule> getModule() const;

  virtual std::shared_ptr<IOutputPlug> plugIn(std::shared_ptr<IInput>);

  virtual void unPlug(std::shared_ptr<IInput>);

  virtual int getType() const;

  virtual std::list<std::shared_ptr<IInput>> getConnectedInputs() const;

  virtual std::shared_ptr<IInput> getPatchedInput() const;

  virtual void setPatchedInput(std::shared_ptr<IInput> in);

  virtual void unPatch();

private:
  std::shared_ptr<IModule> m_module;
  int m_typeID;
  typedef std::shared_ptr<IOutputPlug> IOutputPlugPtr;
  typedef std::list<IOutputPlugPtr> PlugList;
  PlugList m_plugs;
  IType *m_data;

  std::shared_ptr<IInput> m_patchedInput;

  int m_index;
  const COutputVTable *m_vtable;
  void *m_instance;
};

#endif
