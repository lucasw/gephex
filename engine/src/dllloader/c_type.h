#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H

#include "interfaces/itype.h"

class CTypeVTable;

/** 
 * This implementation of the IType interface uses a structure with
 * function pointers to create a type object.
 */
class CType : public IType 
{
 public:
  CType(void* instance,const CTypeVTable& ftab, bool isOwner = false);
  virtual ~CType();
  
  virtual void assign(const IType*);
  
  virtual bool serialize (utils::Buffer& b) const;
  virtual void deSerialize (const utils::Buffer& buf);
  
  virtual bool equalAttributes(const TypeAttributes& attr) const;
  
  virtual void convert(const IType& src, const TypeAttributes& attr);

  virtual void* getPointer() const;
  
 private:
  CType(const CType&); // nicht impl.
  const CType& operator=(const CType&); // nicht impl.
  
  const CTypeVTable* const vTab;
  mutable void* instance;
  const bool amOwner;
};

#endif
