#ifndef INCLUDED_ITYPE_CLASS_H
#define INCLUDED_ITYPE_CLASS_H

class IType;

class ITypeClass
{
public:
	virtual ~ITypeClass() {}
	virtual ITypeClass* clone() const = 0;
	virtual IType* buildInstance() const = 0;
};

#endif
