#include "modulefactory.h"
//#include "imodule.h"
#include "interfaces/imoduleclass.h"

#include <stdexcept>

namespace renderer
{

  ModuleFactory::ModuleFactory() : moduleClasses()
  {
  }

  ModuleFactory::~ModuleFactory()
  {
  }

  IModule* ModuleFactory::buildNewModule(const std::string& name,
					 const ITypeFactory& tFactory) const
  {
    ClassMap::const_iterator i = moduleClasses.find(name);
    if (i == moduleClasses.end())
      {
	throw std::runtime_error("Ungültige Modulklassen ID");
      }

    return i->second->buildInstance(tFactory);
    //irgendwo muss man die nopch herholen
    // oder in jedem IModule speichern :)
  }


  void ModuleFactory::registerModuleClass(const std::string& name,
					  const IModuleClass& moduleClass)
  {
    ClassMap::const_iterator i = moduleClasses.find(name);
    if (i != moduleClasses.end())
      {
	throw std::runtime_error("Modul ID existiert bereits bei "
				 "ModuleFactory::registerModuleClass()");
      }
	
    moduleClasses[name] = utils::AutoPtr<IModuleClass>(moduleClass.clone());
  }

  void ModuleFactory::unregisterModuleClass(const std::string& name)
  {
    ClassMap::iterator i = moduleClasses.find(name);
    if (i == moduleClasses.end())
      {
	throw std::runtime_error("Modul ID existiert nicht bei "
				 "ModuleFactory::unregisterModuleClass()");
      }

    moduleClasses.erase(i);
  }

  /*  std::list<std::string> ModuleFactory::getAllNames() const
  {
    std::list<std::string> liste;
    for (ClassMap::const_iterator i = moduleClasses.begin();
	 i != moduleClasses.end(); ++i)
      {
	liste.push_back(i->first);
      }
	
    return liste;
    }*/

} // end of namespace
