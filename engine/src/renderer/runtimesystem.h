#ifndef INCLUDED_RUNTIMESYSTEM_H
#define INCLUDED_RUNTIMESYSTEM_H

#include <list>
#include <string>
#include <map>
#include "utils/autoptr.h"

class ITypeFactory;

class IModule;

class IControlValueReceiver;
class IModuleStatisticsReceiver;

namespace utils {
  class ILogger;
  class Buffer;
}

namespace renderer
{

  class IModuleFactory;

  class ModuleControlBlock;
  class IModuleFactory;

  class RuntimeSystem
  {
  public:
    RuntimeSystem(const IModuleFactory&, const ITypeFactory&,
				  utils::AutoPtr<utils::ILogger>& logger);
    virtual ~RuntimeSystem ();

    virtual void connect(int m1,int outputIndex,int m2,int inputIndex);

    virtual void disconnect(int m1,int inputIndex);

    virtual void update(IControlValueReceiver* cvr,
			IModuleStatisticsReceiver* msr);

    virtual void deleteModule(int);	

    virtual void addModule(const std::string& moduleClassName, int moduleID);

    virtual void setInputValue(int moduleID,int inputIndex,
			       const utils::Buffer& buf,
			       IControlValueReceiver* cvr);

    virtual void syncInputValue(int nodeID, int inputIndex,
				IControlValueReceiver* cvr) const;

    virtual void synchronizeInputValues(IControlValueReceiver* cvr) const;

    typedef utils::AutoPtr<ModuleControlBlock> ModuleControlBlockPtr;
    typedef std::map<int, ModuleControlBlockPtr> ControlBlockMap;
  private:
    ControlBlockMap m_modules; // ID -> IModule*
    std::list<ModuleControlBlockPtr> m_sinks; // Liste aller Senken
    int m_time;
    int frameCount;

    ModuleControlBlockPtr getControlBlock(IModule*);

    const IModuleFactory& moduleFactory;
    const ITypeFactory& typeFactory;
	utils::AutoPtr<utils::ILogger>& m_logger;
  };

} // end of namespace renderer

#endif


