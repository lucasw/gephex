/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
#include "interfaces/igraphdatasender.h"
#include "interfaces/iserializedgraphsender.h"
#include "interfaces/ismartcontrolvaluereceiver.h"
#include "interfaces/icontrolvaluesender.h"
#include "interfaces/irenderercontrolsender.h"
#include "interfaces/imodulestatisticssender.h"
#include "interfaces/imodulestatisticssmartreceiver.h"
#include "interfaces/imodelstatussender.h"

namespace utils {
  class ILogger;
  class Buffer;
}

class IModuleClassSpec;
class ISerializedGraphReceiver;


namespace model
{

  class Graph;
  class GraphFileSystem;
  class ControlValueSet;

  class Model: 
    public IModelControlReceiver, 
    public IModuleClassSpecReceiver,

    public IModuleConstructionSmartSender, 
    public IModuleConstructionDumbSender, 
    public IGraphNameSender,
    public IModuleDataSender,
    public IGraphDataSender,
    public ISerializedGraphSender,
    public ISmartControlValueReceiver,
    public IControlValueSender,
    public IRendererControlSender,
    public IModuleStatisticsSmartReceiver,
    public IModuleStatisticsSender,
    public IModelStatusSender
    {
    public:
      Model(const std::string graph_path,
            utils::AutoPtr<utils::ILogger>& logger);

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

      virtual void setEditGraphData(int type, const utils::Buffer& buf);
      virtual void unSetEditGraphData(int type);

      void newGraphWithID(const std::string& graphName,
                          const std::string& graphID,
                          bool notifyAndCreate = true);

      virtual void newGraph(const std::string& graphName);

      virtual void renameGraph(const std::string& graphID,
			       const std::string& newGraphName);

      virtual void copyGraph(const std::string& srcGraphID,
			     const std::string& dstGraphName);

      virtual void saveGraph(const std::string& graphID);

      virtual void deleteGraph(const std::string& graphName);

      virtual void newControlValueSet(const std::string& graphID,
				       const std::string& SetNme);

      void newControlValueSetWithID(const std::string& graphID,
                                    const std::string& SetNme,
                                    const std::string& snapID);

      virtual void renameControlValueSet(const std::string& graphID,
                                         const std::string& snapID,
                                         const std::string& newSnapName);

      virtual void copyControlValueSet(const std::string& graphID,
                                       const std::string& snapID,
                                       const std::string& newSnapName);

      virtual void deleteControlValueSet(const std::string& graphID,
                                         const std::string& snapID);

      //TODO: war mal const
      virtual void synchronize();

      void sendExistingGraphs();

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

      virtual void registerGraphDataReceiver(IGraphDataReceiver&);

      virtual void registerSerializedGraphReceiver(ISerializedGraphReceiver&);
      virtual void registerRendererControlReceiver(IRendererControlReceiver&);

      // from ISmartControlValueReceiver
      virtual void controlValueChanged(const std::string& graphName,
				       int nodeID,int intputIndex,
				       const utils::Buffer& newValue);

      virtual void syncInputValuesStarted(const std::string& graphName);
      virtual void syncInputValuesFinished(const std::string& graphName);

      // from  IControlValueSender
      virtual void registerControlValueReceiver(IControlValueReceiver& r);

      virtual void deserializeGraph(const std::string& graphstream);
      virtual void serializeGraph(const std::string& graphName);

      void updateFileSystem();

      /**
       * check if a graph with such a ID exists in the model
       * \param graph_id is the id of the graph to check for
       * \returns true if it exists
       */
      bool check_for_graph_id(const std::string& graph_id);

      /**
       * check if a snapshot with such a ID exists in the model
       * \param graph_id is the id of the graph to check for
       * \param snap_id is the id of the snapshot to check for
       * \returns true if it exists
       */
      bool check_for_snap_id(const std::string& graph_id,
			     const std::string& snap_id);
      
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
      utils::AutoPtr<Graph> editGraph;     // this can be edited by the gui
      utils::AutoPtr<ControlValueSet> editControlSet;
      utils::AutoPtr<ControlValueSet> renderedControlSet;

      std::map<std::string, bool> knownGraphIDs;
      std::map<std::string, bool> knownSnapIDs;

      IModuleConstructionDumbReceiver* dumbo;
      IModuleConstructionSmartReceiver* smartAss;	
      IGraphNameReceiver* gnr;
      ISerializedGraphReceiver* serializedGraphReceiver;
      IRendererControlReceiver* rendererControlReceiver;
      IModuleDataReceiver* dr;
      IGraphDataReceiver* gr;
      IControlValueReceiver* controlValueReceiver;
      IModuleStatisticsReceiver* moduleStatisticsReceiver;
      IModelStatusReceiver* modelStatusReceiver;

      utils::AutoPtr<utils::ILogger> m_logger;

      // helper functions
      void deleteModule(utils::AutoPtr<Graph>, int moduleID);

#ifndef NDEBUG
      void checkGraphSerialisation();
#endif

    };

}

#endif
