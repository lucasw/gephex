#ifndef __INCLUDED_MODEL_H__
#define __INCLUDED_MODEL_H__

#include <string>
#include <map>
#include <vector>
#include "utils/autoptr.h"

#include "specmap.h"

#include "interfaces/imoduleconstructiondumbsender.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/igraphnamesender.h"
#include "interfaces/imodelcontrolreceiver.h" 
#include "interfaces/imoduleconstructionsmartsender.h" 
#include "interfaces/imoduleconstructiondumbsender.h"
#include "interfaces/imoduledatasender.h"
#include "interfaces/iserializedgraphsender.h"
#include "interfaces/ismartcontrolvaluereceiver.h"
#include "interfaces/icontrolvaluesender.h"
#include "interfaces/irenderercontrolsender.h"
#include "interfaces/imodulestatisticssender.h"
#include "interfaces/imodulestatisticssmartreceiver.h"
#include "interfaces/imodelstatussender.h"

namespace utils {
  class Buffer;
}

class IModuleClassSpec;
class ISerializedGraphReceiver;


namespace model
{

  class Graph;
  class GraphFileSystem;
  class ControllValueSet;

  class Model: 
    public IModelControlReceiver, 
    public IModuleClassSpecReceiver,

    public IModuleConstructionSmartSender, 
    public IModuleConstructionDumbSender, 
    public IGraphNameSender,
    public IModuleDataSender,
    public ISerializedGraphSender,
    public ISmartControlValueReceiver,
    public IControlValueSender,
    public IRendererControlSender,
    public IModuleStatisticsSmartReceiver,
    public IModuleStatisticsSender,
    public IModelStatusSender
    {
    public:
      Model(const std::string basepath_);
      virtual ~Model();

      // from IModelControlReceiver
      virtual void addModule(const std::string& moduleClassName) ;
      virtual void connectModules(int moduleID1,int outputIndex,
				  int moduleID2,int inputIndex);
      virtual void disconnectModules(int moduleID,int inputIndex) ;
      virtual void deleteModule(int moduleID) ;
      virtual void setModuleData(int moduleID,int type,
				 const utils::Buffer& buf);

      virtual void unSetModuleData(int moduleID,int type);

      void newGraphWithID(const std::string& graphName,
			  const std::string& graphID);

      virtual void newGraph(const std::string& graphName);

      virtual void renameGraph(const std::string& graphID,
			       const std::string& newGraphName);

      virtual void copyGraph(const std::string& srcGraphID,
			     const std::string& dstGraphName);

      virtual void saveGraph(const std::string& graphID);

      virtual void deleteGraph(const std::string& graphName);

      virtual void newControllValueSet(const std::string& graphID,
				       const std::string& SetNme);

      virtual void renameControllValueSet(const std::string& graphID,
					  const std::string& snapID,
					  const std::string& newSnapName);

      virtual void copyControllValueSet(const std::string& graphID,
					const std::string& snapID,
					const std::string& newSnapName);

      virtual void deleteControllValueSet(const std::string& graphID,
					  const std::string& snapID);

      //TODO: war mal const
      virtual void synchronize();

      virtual void changeRenderedGraph(const std::string& graphName, const std::string& snapShot);
      virtual void changeEditGraph(const std::string& graphName, const std::string& snapShot);

      virtual void setInputValue(int moduleID, int inputIndex,
				 const utils::Buffer& buf);

      //TODO: war mal const
      virtual void syncInputValue(int moduleID, int inputIndex);

      // from IModuleClassSpecReceiver
      virtual void moduleClassLoaded(const std::string& moduleClassName,const IModuleClassSpec&);
      virtual void moduleClassUnloaded(const std::string& moduleClassName);

      virtual void registerModuleConstructionDumbReceiver(IModuleConstructionDumbReceiver&);
      virtual void registerModuleConstructionSmartReceiver(IModuleConstructionSmartReceiver&);
      virtual void registerGraphNameReceiver(IGraphNameReceiver&);
      virtual void registerModuleDataReceiver(IModuleDataReceiver&);
      virtual void registerSerializedGraphReceiver(ISerializedGraphReceiver&);
      virtual void registerRendererControlReceiver(IRendererControlReceiver&);

      // from ISmartControllValueReceiver
      virtual void controlValueChanged(const std::string& graphName,
				       int nodeID,int intputIndex,
				       const utils::Buffer& newValue);

      virtual void syncInputValuesStarted(const std::string& graphName);
      virtual void syncInputValuesFinished(const std::string& graphName);

      // from  IControllValueSender
      virtual void registerControlValueReceiver(IControlValueReceiver& r);

      virtual void deserializeGraph(const std::string& graphstream);
      virtual void serializeGraph(const std::string& graphName);

      void updateFileSystem();

      virtual void modExecTimeSignal(const std::string& graphName,
				     int nodeID, double execTime);

      void registerModuleStatisticsReceiver(IModuleStatisticsReceiver& r);

      void registerModelStatusReceiver(IModelStatusReceiver& r);

      typedef  std::map<std::string,utils::AutoPtr<Graph> > GraphMap;  
    private:
      utils::AutoPtr<GraphFileSystem> fileSystem;

      // all loaded graphs
      GraphMap graphs;

      // to build a new module
      SpecMap specs;

      utils::AutoPtr<Graph> renderedGraph; // this is shown by the renderer
      utils::AutoPtr<Graph> editGraph; // this can be edited by the gui
      utils::AutoPtr<ControllValueSet> editControllSet;
      utils::AutoPtr<ControllValueSet> renderedControllSet;

      std::map<std::string, bool> knownGraphIDs;
	  std::map<std::string, bool> knownSnapIDs;
      // helper functions
      void deleteModule(utils::AutoPtr<Graph>, int moduleID);      

      IModuleConstructionDumbReceiver* dumbo;
      IModuleConstructionSmartReceiver* smartAss;	
      IGraphNameReceiver* gnr;
      ISerializedGraphReceiver* serializedGraphReceiver;
      IRendererControlReceiver* rendererControlReceiver;
      IModuleDataReceiver* dr;
      IControlValueReceiver* controlValueReceiver;
      IModuleStatisticsReceiver* moduleStatisticsReceiver;
      IModelStatusReceiver* modelStatusReceiver;

#ifndef NDEBUG
      void Model::checkGraphSerialisation();
#endif

    };

}

#endif
