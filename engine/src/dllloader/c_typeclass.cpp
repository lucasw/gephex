#include "c_typeclass.h"

#include "c_typetables.h"
#include "c_type.h"

CTypeClass::CTypeClass(const CTypeFunctionTable& ftab_)						  
 : functionTable(new CTypeFunctionTable(ftab_))
{
}

CTypeClass::~CTypeClass()
{
	delete functionTable;
}

ITypeClass* CTypeClass::clone() const
{
  return new CTypeClass(*this->functionTable);
}

IType* CTypeClass::buildInstance(/*void* ptr*/) const
{
  /*	if (ptr == 0) 
	{*/
		void* instance = functionTable->newInstance();
		return new CType(instance,*functionTable,true);
		/*	}
	else 
	{
		return new CType(ptr,*functionTable,false);
		}*/
	
}
