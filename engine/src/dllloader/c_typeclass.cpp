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
