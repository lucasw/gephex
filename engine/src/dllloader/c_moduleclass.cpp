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
