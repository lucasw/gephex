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

#include "utils/autoptr.h"

#include "frei0rwrapper.h"

class CModuleFunctionTable;
class CModuleAttributes;
class IType;

class CModuleClass : public IModuleClass
{

  CModuleClass& operator=(const CModuleClass&); // nicht impl.
  CModuleClass(const CModuleClass&); // nicht. impl

public:

	CModuleClass(const CModuleFunctionTable&,
		     const CModuleAttributes& attr_,
		     const std::string& name,
		     frei0r_funs_t* frei0r,
                     int frei0r_plugin_type);

	virtual IModuleClass* clone() const;

	virtual ~CModuleClass();

	virtual IModule* buildInstance(const ITypeFactory& tFactory) const;

private:

	CModuleFunctionTable* functionTable;
	CModuleAttributes* attributes;
	typedef utils::AutoPtr<IType> ITypePtr;
	mutable std::vector<ITypePtr> defaultInputValues;
	std::string m_name;
	frei0r_funs_t* m_frei0r;
        int m_frei0r_plugin_type;
};

#endif
