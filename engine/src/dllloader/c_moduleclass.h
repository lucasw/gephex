#ifndef INCLUDED_CMODULE_CLASS_H
#define INCLUDED_CMODULE_CLASS_H

#include <vector>

#include "interfaces/imoduleclass.h"

#include "utils/autoptr.h"

class CModuleFunctionTable;
class CModuleAttributes;
class IType;

class CModuleClass : public IModuleClass
{

  CModuleClass& operator=(const CModuleClass&); // nicht impl.
  CModuleClass(const CModuleClass&); // nicht. impl

public:

	CModuleClass(const CModuleFunctionTable&,
		     const CModuleAttributes& attr_);

	virtual IModuleClass* clone() const;

	virtual ~CModuleClass();

	virtual IModule* buildInstance(const ITypeFactory& tFactory) const;

private:

	CModuleFunctionTable* functionTable;
	CModuleAttributes* attributes;
	typedef utils::AutoPtr<IType> ITypePtr;
	mutable std::vector<ITypePtr> defaultInputValues;
};

#endif
