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

#include "c_typeclass.h"

#include "c_typetables.h"
#include "c_type.h"

CTypeClass::CTypeClass(const CTypeFunctionTable& ftab_,std::string name,int id)
  : functionTable(ftab_), typeName(name), typeId(id)
{
}

CTypeClass::~CTypeClass()
{
}

ITypeClass* CTypeClass::clone() const
{
  return new CTypeClass(functionTable,typeName,typeId);
}

IType* CTypeClass::buildInstance(/*void* ptr*/) const
{
  /*	if (ptr == 0) 
	{*/
  void* instance = functionTable.newInstance();
  return new CType(instance,functionTable,true);
		/*	}
	else 
	{
		return new CType(ptr,*functionTable,false);
		}*/
	
}
