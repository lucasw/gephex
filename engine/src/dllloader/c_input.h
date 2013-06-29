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

#ifndef INCLUDED_INPUT_H
#define INCLUDED_INPUT_H

#include "interfaces/imodule.h"

class ITypeFactory;

namespace utils {
	class Buffer;
}

class CInputVTable;

class CInput : public IInput
{
public:	
	/**
	* defaultValue must exist at least as long as this instance.
	* TODO: make defaultValue a static IType that is shared
	* among all modules of the same kind.
	*/
	CInput(int _typeID,bool _const,bool _strong,
	       IModule&, int index, const ITypeFactory& factory_,
		   const TypeAttributes* attr, IType& defaultValue,
		   const CInputVTable& vtable, void* instance);

	virtual ~CInput();

	virtual const IType* getData() const;

	virtual IModule* getConnectedModule() const;

	//	virtual bool hasChanged() const;

	virtual void plugIn(utils::AutoPtr<IOutputPlug>& oPlug)
	  throw (std::runtime_error);

	virtual void unPlug();

	virtual int getType() const;

	virtual bool isConst() const;

	virtual bool isStrongDependency() const;

	virtual void setValue(const utils::Buffer& serializedData);

	virtual int getIndex() const;

	virtual IModule* getModule() const;

	virtual const TypeAttributes* getTypeAttributes() const;

	virtual void update();

private:
	bool m_isConnected;

	IType* m_defaultValue; // default value
	const IType* data; // pointer to the valid value this is returned to the module
	IType* internalData;	
	utils::AutoPtr<IOutputPlug> oPlug;
	int typeID;
	bool _isConst;
	bool _isStrong;
	IModule* mod;
        int m_index;
	//	mutable bool changed;
	const ITypeFactory* factory;
	const TypeAttributes* m_attr;

	const CInputVTable* m_vtable;
	void* m_instance;
};

#endif
