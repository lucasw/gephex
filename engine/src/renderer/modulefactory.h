#ifndef INCLUDED_MODULEFACTORY_H
#define INCLUDED_MODULEFACTORY_H

#include <list>
#include <map>
#include <string>

#include "utils/autoptr.h"

class IModule;
class IModuleClass;
class ITypeFactory;

namespace renderer
{

class IModuleFactory
{
public:
  virtual IModule* buildNewModule(const std::string& className,
				  const ITypeFactory&) const = 0;

};

class ModuleRegistry
{
public:
  virtual void registerModuleClass(const std::string& classNme,
				   const IModuleClass& moduleClass) = 0;

  virtual void unregisterModuleClass(const std::string& classNme) = 0;
};

class ModuleFactory : public IModuleFactory, public ModuleRegistry//TODO
{
public:
  ModuleFactory();
  virtual ~ModuleFactory();
  virtual IModule* buildNewModule(const std::string& className,
				  const ITypeFactory&) const;

  virtual void registerModuleClass(const std::string& className,
				   const IModuleClass& moduleClass);

  virtual void unregisterModuleClass(const std::string& classNme);

  //  virtual std::list<std::string> getAllNames() const;// todo

private:
  typedef std::map<const std::string,utils::AutoPtr<IModuleClass> > ClassMap;
  ClassMap moduleClasses;
};

} // end of namespace

#endif
