#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H

#include "interfaces/itype.h"

class CTypeVTable;
//class TypeFunctionTable;

class CType : public IType {
private:

	CType(const CType&); // nicht impl.
	const CType& operator=(const CType&); // nicht impl.

	public:
		CType(void* instance,CTypeVTable& ftab,bool isOwner = false);
		virtual ~CType();

		virtual void assign(const IType*);
		
		virtual utils::Buffer serialize () const;
		virtual void deSerialize (const utils::Buffer& buf);

		virtual void* getPointer() const;

		virtual bool equalAttributes(const TypeAttributes& attr) const;

		virtual void convert(const IType& src, const TypeAttributes& attr);

	private:
		CTypeVTable *vTab;
		mutable void* instance;
		const bool amOwner;
};

#endif
