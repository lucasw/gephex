#include "typefactory.h"
//#include "itype.h"

#include "interfaces/itypeclass.h"

#include <stdexcept>

namespace renderer
{

TypeFactory::TypeFactory() : typeClasses()
{
}

TypeFactory::~TypeFactory()
{
}

IType* TypeFactory::buildNew(int id/*,void* ptr*/) const //TODO void* muss weg
{
	ClassMap::const_iterator i = typeClasses.find(id);
	if (i == typeClasses.end())
	{
		throw std::runtime_error("Ungültige  ID");
	}

	utils::AutoPtr<ITypeClass> tClass = i->second;

	IType* newType = tClass->buildInstance();
	return newType;
}

void TypeFactory::registerTypeClass(int id,const ITypeClass& typeClass)
{
	ClassMap::const_iterator i = typeClasses.find(id);
	if (i != typeClasses.end())
	{
	  throw std::runtime_error("Typ ID existiert bereits");
	}
	
	typeClasses[id] = utils::AutoPtr<ITypeClass>( typeClass.clone() );
}

} // end of namespace
