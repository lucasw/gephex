#ifndef INCLUDED_CTYPE_CLASS_H
#define INCLUDED_CTYPE_CLASS_H

#include "interfaces/itypeclass.h"

class IType;
class CTypeFunctionTable;

class CTypeClass : public ITypeClass
{

	CTypeClass(const CTypeClass&); //nicht impl.
	CTypeClass& operator=(const CTypeClass&); //nicht impl.
public:
	CTypeClass(const CTypeFunctionTable&);

	virtual ~CTypeClass();
	virtual ITypeClass* clone() const;
	virtual IType* buildInstance(/*void* ptr*/) const; //TODO void* muss weg

private:
	CTypeFunctionTable* functionTable;
};

#endif
