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

#include "c_moduleclass.h"

#include "c_module.h"

#include "c_moduletables.h"

#include "renderer/typefactory.h" //TODO: not allowed
#include "interfaces/itype.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

/*CModuleClass::CModuleClass(const CModuleClass& mc)
  : functionTable(new CModuleFunctionTable(*mc.functionTable)), 
  attributes(new CModuleAttributes(*mc.attributes))
{
}*/

CModuleClass::CModuleClass(const CModuleFunctionTable& ftab_,
			   const CModuleAttributes& attr_,
			   const std::string& name)
  : functionTable(new CModuleFunctionTable(ftab_)), 
  attributes(new CModuleAttributes(attr_)), 
  defaultInputValues(attr_.inputs.size()),
  m_name(name)
{
}

IModuleClass* CModuleClass::clone() const
{
  CModuleClass* newClass = new CModuleClass(*this->functionTable,
	  *this->attributes,
	  this->m_name);
  newClass->defaultInputValues = defaultInputValues;
  return newClass;
}



CModuleClass::~CModuleClass()
{
  delete functionTable;
  delete attributes;
}


IModule* CModuleClass::buildInstance(const ITypeFactory& tFactory) const

{
  void* instance = functionTable->newInstance();
  if (instance == 0)
    {
      throw std::runtime_error("Ungute Sache vorgefallen.");
    }

  // Create the default inputs, if any
  if (defaultInputValues.size() > 0 && defaultInputValues[0] == 0)
    {
#if (ENGINE_VERBOSITY > 0)
      std::cout << "Creating default values for inputs" << std::endl;
#endif
      for (unsigned int i = 0; i < defaultInputValues.size(); ++i)
	{

	  ITypePtr tmp(tFactory.buildNew(attributes->inputs[i]));

	  //TODO
	  const TypeAttributes* attr = attributes->fixedAttributes[i];
	    if (attr != 0 && !tmp->equalAttributes(*attr))
	      {
		//throw std::runtime_error("Type conversion of default"
		//			 "inputs not implemented yet");
                
                // can throw
		tmp->convert(*tmp, *attr);
	      }
	    defaultInputValues[i] = tmp;
	}
    }

  return new CModule(instance,*functionTable,*attributes,
		     tFactory,defaultInputValues, m_name);
}
