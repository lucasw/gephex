#ifndef INCLUDED_CTYPE_CLASS_H
#define INCLUDED_CTYPE_CLASS_H

#include <string>
#include "interfaces/itypeclass.h"
#include "c_typetables.h"

class IType;
class CTypeFunctionTable;

class CTypeClass : public ITypeClass
{
 public:
  CTypeClass(const CTypeFunctionTable&, std::string name, int id);
  virtual ~CTypeClass();
  virtual ITypeClass* clone() const;
  //TODO void* muss weg
  virtual IType* buildInstance(/*void* ptr*/) const; 

 private:
  CTypeFunctionTable functionTable;
  std::string typeName;
  int typeId;
  
  CTypeClass(const CTypeClass&); //not impl.
  CTypeClass& operator=(const CTypeClass&); //not impl.
};

#endif
