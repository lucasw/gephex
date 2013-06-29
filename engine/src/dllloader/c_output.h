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

#include "interfaces/imodule.h"

#include "utils/autoptr.h"

class COutputPlug;

class COutputVTable;

class COutput : public IOutput
{
public:
	COutput(IModule& mod,int _typeID, IType* data, int index,
			const COutputVTable& vtable, void* instance);
	virtual ~COutput();

	//virtual void setData(const IType* data); //TODO: remove?

	virtual IModule* getModule() const;

	virtual utils::AutoPtr<IOutputPlug> plugIn(IInput&);

	virtual void unPlug(IInput &);

	virtual int getType() const;

  virtual std::list<IInput*> getConnectedInputs() const;

  virtual IInput* getPatchedInput() const;

  
  virtual void setPatchedInput(IInput* in);

  
  virtual void unPatch();

private:
	IModule* m_module;
	int m_typeID;
	typedef utils::AutoPtr<IOutputPlug> IOutputPlugPtr;
	typedef std::list<IOutputPlugPtr> PlugList;
	PlugList m_plugs;
	IType* m_data;

	IInput* m_patchedInput;

	int m_index;
	const COutputVTable* m_vtable;
	void* m_instance;
};

#endif
