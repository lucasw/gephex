#ifndef INCLUDED_TYPEFACTORY_H
#define INCLUDED_TYPEFACTORY_H

#include <list>
#include <map>

#include "interfaces/itypefactory.h"
#include "utils/autoptr.h"

class IType;
class ITypeClass;

namespace renderer
{

class TypeRegistry
{
public:
  virtual void registerTypeClass(int id,const ITypeClass& typeClass) = 0;
};

class TypeFactory : public ITypeFactory, public TypeRegistry
{
public:
  TypeFactory();
  virtual ~TypeFactory();
  virtual IType* buildNew(int id) const;
  
  virtual void registerTypeClass(int id, const ITypeClass& typeClass);

private:
  typedef std::map<int, utils::AutoPtr<ITypeClass> > ClassMap;
  ClassMap typeClasses;
};

} //end of namespace

#endif

