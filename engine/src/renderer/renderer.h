#ifndef INCLUDED_RENDERER_H
#define INCLUDED_RENDERER_H

#include <map>
#include <string>

//TODO: only necessary because the forward declarations are missing in the
//      auto generated header imoduleclassreceiver.h and itypeclassreceiver.h
class IModuleClass;
class ITypeClass;

#include "interfaces/irenderercontrolreceiver.h"
#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/itypeclassreceiver.h"
#include "interfaces/imoduleconstructionsmartreceiver.h"

#include "interfaces/ismartcontrolvaluesender.h"
#include "interfaces/imodulestatisticssmartsender.h"
#include "interfaces/irendererstatussender.h"

#include "interfaces/itask.h"
#include "utils/autoptr.h"
//#include "runtimesystem.h"

namespace utils {
  class Buffer;
  class ILogger;
}

namespace renderer
{

  class ModuleFactory;
  class TypeFactory;
  class RuntimeSystem;

  class Renderer :
    public IRendererControlReceiver, 
    public IModuleClassReceiver,
    public ITypeClassReceiver,
    public IModuleConstructionSmartReceiver,
    public ISmartControlValueSender,
    public IModuleStatisticsSmartSender,
    public IRendererStatusSender,
    public ITask
  {
  public:
    Renderer(utils::AutoPtr<utils::ILogger>& logger);

    virtual ~Renderer();

    // from IControlValueSender
    virtual void registerSmartControlValueReceiver(ISmartControlValueReceiver& r);
  
    // from IModuleStatisticsSender
    virtual void registerModuleStatisticsSmartReceiver(IModuleStatisticsSmartReceiver& r);

    // from IRendererStatusSender
    virtual void registerRendererStatusReceiver(IRendererStatusReceiver& r);

    // from ITask
    virtual bool run();

    // from IRendererControlReceiver
    virtual void start();
    virtual void stop();


    // from IModuleClassReceiver	
    virtual void moduleClassLoaded(const std::string& moduleClassName,const IModuleClass& moduleClass);
    virtual void moduleClassUnloaded(const std::string& moduleClassName);

    // from ITypeClassReceiver
    virtual void typeClassLoaded(int typeClassID,const ITypeClass& moduleClass);
    virtual void typeClassUnloaded(int typeClassID);

    // from IModuleConstructionSmartReceiver
    virtual void moduleAdded(const std::string& graphID, const std::string& moduleClassID,int modID);
    virtual void modulesConnected(const std::string& graphID, int moduleID1,int outputIndex, int moduleID2,int inputIndex);
    virtual void modulesDisconnected(const std::string& graphID, int moduleID,int inputIndex);
    virtual void moduleDeleted(const std::string& graphID, int moduleID);
    virtual void newGraphCreated(const std::string& graphID);
    /*    virtual void graphRenamed(const std::string& graphID,
	  const std::string& newGraphName);*/
    virtual void graphChanged(const std::string& graphID);

	virtual void graphDeleted(const std::string& graphID);

    // rest ???

    virtual void setInputValue(const std::string& graphID,
			       int nodeID,int inputIndex,
			       const utils::Buffer& buf);

    //TODO: war mal const
    virtual void syncInputValue(const std::string& graphID,
				int nodeID, int inputIndex);

    //TODO: war mal const
    virtual void synchronizeInputValues(const std::string& graphID);

	void synchronize();

  private:
    typedef std::map<const std::string,utils::AutoPtr<RuntimeSystem> > RuntimeSystemMap;
    RuntimeSystemMap graphs;

    bool isStarted;

    utils::AutoPtr<RuntimeSystem> activeGraph;
    std::string activeGraphName; //TODO

    ISmartControlValueReceiver* cvr;
    IModuleStatisticsSmartReceiver* msr;
    IRendererStatusReceiver* rendererStatusReceiver;

    utils::AutoPtr<ModuleFactory> moduleFactory;
    utils::AutoPtr<TypeFactory> typeFactory;


    utils::AutoPtr<RuntimeSystem> find(const std::string& graphID) const;

    utils::AutoPtr<utils::ILogger> m_logger;
  };

}

#endif

