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

#ifndef INCLUDED_CMODULE_CLASS_H
#define INCLUDED_CMODULE_CLASS_H

#include <vector>

#include "interfaces/imoduleclass.h"
#include "moduleclassspec.h"

#include "c_moduletables.h"
#include "utils/autoptr.h"
#include "utils/buffer.h"

class CModuleFunctionTable;
class CModuleAttributes;
class IType;
class NameResolver;

class CModuleClass : public IModuleClass
{

  CModuleClass& operator=(const CModuleClass&); // nicht impl.
  CModuleClass(const CModuleClass&); // nicht. impl

public:

  CModuleClass(const CModuleFunctionTable& ft,
	       NameResolver& resolver);

	virtual const std::string& name() const;
	virtual const utils::Buffer& info() const;
	virtual const ModuleClassSpec& spec() const;
	virtual ~CModuleClass();

	virtual IModule* buildInstance(const ITypeFactory& tFactory) const;

private:
	const CModuleFunctionTable m_functionTable;
	CModuleAttributes m_attributes;
	mutable std::vector<IType*> m_defaultInputValues;
	std::string m_name;
	utils::Buffer m_info;
	utils::AutoPtr<ModuleClassSpec> m_spec;
};

#endif
