#ifndef INCLUDED_MODULE_CLASS_MODEL_H
#define INCLUDED_MODULE_CLASS_MODEL_H

#include <list>

#include "interfaces/imoduleclassinforeceiver.h"

namespace utils {
	class Buffer;
}

namespace gui
{
  class IModuleClassView;
  
  class ModuleClassModel : public IModuleClassInfoReceiver
  {
  public:
    virtual ~ModuleClassModel();

    void registerModuleClassView(IModuleClassView&);
    void unregisterModuleClassViews();
    
    void moduleClassLoaded(const std::string& moduleClassName,
			   const utils::Buffer&);

    void moduleClassUnloaded(const std::string& moduleClassName);

    void syncStarted();
    void syncFinished();
    
  private:
	  std::list<IModuleClassView*> views;
    
  };
}
#endif
