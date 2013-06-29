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

#include "model.h"

#include <list>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <algorithm>

#include "graph.h"
#include "graphserial.h"
#include "graphnode.h"
#include "graphconnection.h"
#include "graphfilesystem.h"
#include "controlvalueset.h"

#include "utils/autoptr.h"
#include "utils/ilogger.h"

#include "interfaces/igraphnamereceiver.h"
#include "interfaces/imoduleconstructionsmartreceiver.h"
#include "interfaces/imoduleconstructiondumbreceiver.h"
#include "interfaces/imoduledatareceiver.h"
#include "interfaces/igraphdatareceiver.h"
#include "interfaces/iserializedgraphreceiver.h"
#include "interfaces/irenderercontrolreceiver.h"

#include "interfaces/imoduleclassspec.h"
#include "interfaces/icontrolvaluereceiver.h"
#include "interfaces/imodulestatisticsreceiver.h"
#include "interfaces/imodelstatusreceiver.h"


#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

namespace model
{
  
  namespace
  {

    class has_name
    {
    public:
      has_name(const std::string& name) : m_name( name ) {}
      bool operator()(const Model::GraphMap::value_type& p)
      { 
	return p.second->getName() == m_name;
      }
    private:
      const std::string m_name;
    };

    bool isDirectoryName(const std::string& name)
    {
      //TODO: changed assert to this test
      // dunno why it is needed
      if (name.length() <= 2)
        return false;
      return *(name.end()-1)=='/';
    }
    
    // Teilt einem IModuleConstructionDumbReceiver mit, dass alle Module
    // und Connections eines Graphen gelöscht wurden.
    void sendGraphDestruction(const Graph& g,
			      IModuleConstructionDumbReceiver& dumbo,
			      IModuleDataReceiver& dr,
                              IGraphDataReceiver& gr)
    {
      const Graph::ConnectionMap& connections = g.connections();

      for (Graph::ConnectionMap::const_iterator it = connections.begin();
	   it != connections.end(); ++it)
	{
	  assert(it->first.first == it->second->id2() &&
		 it->first.second == it->second->inIndex());
			
	  dumbo.modulesDisconnected(it->second->id2(),
				    it->second->inIndex());
	}

      const std::map<int, utils::Buffer>& data = g.data();
      
      for (std::map<int, utils::Buffer>::const_iterator it = data.begin();
           it != data.end(); ++it)
        {
          gr.graphDataUnSet(it->first);
        }
		
      // unbuild the nodes
      const Graph::GraphNodeList& nodes = g.nodes();
      for (Graph::GraphNodeList::const_iterator jt = nodes.begin();
	   jt != nodes.end(); ++jt)
	{
	  int moduleID = (*jt)->moduleID();
	  std::list<int> moduleDataList = (*jt)->moduleDataList();
	  for (std::list<int>::const_iterator kt = moduleDataList.begin();
	       kt != moduleDataList.end(); ++kt)
	    {
	      dr.moduleDataUnSet(moduleID,*kt);
	    }
			
	  dumbo.moduleDeleted(moduleID);
	}
    }
	
    // Teilt einem IModuleConstructionDumbReceiver mit, dass alle Module
    // und Connections eines Graphen angelegt wurden.
    void sendGraphConstruction(const Graph& g,
			       IModuleConstructionDumbReceiver* dumbo,
			       IModuleDataReceiver* dr,
                               IGraphDataReceiver* gr,
			       IModuleConstructionSmartReceiver* smartAss = 0)
    {
      const std::string graphID = g.getID();
      const Graph::GraphNodeList& nodes = g.nodes();

      if (gr)
        {
          const std::map<int,utils::Buffer>& data = g.data();
          for (std::map<int,utils::Buffer>::const_iterator
                 lt = data.begin(); lt != data.end(); ++lt)
            {
              gr->graphDataSet(lt->first, lt->second);
            }
        }

      for (Graph::GraphNodeList::const_iterator jt = nodes.begin();
	   jt != nodes.end(); ++jt)
	{
	  if (dumbo)
	    dumbo->moduleAdded((*jt)->spec().moduleClassName(),
			       (*jt)->moduleID());
			
	  if (smartAss)
	    smartAss->moduleAdded(graphID,
				  (*jt)->spec().moduleClassName(),
				  (*jt)->moduleID());

          if (dr)
            {			
              const std::map<int,utils::Buffer>& datas = (*jt)->data();
              for (std::map<int,utils::Buffer>::const_iterator 
                     lt = datas.begin(); lt != datas.end(); ++lt)
                {
                  dr->moduleDataSet((*jt)->moduleID(), lt->first,
                                    lt->second);
                }
            }
	}
		
      // build the connections
      const Graph::ConnectionMap& connections = g.connections();
		
      Graph::ConnectionMap::const_iterator kt = connections.begin();
      while(kt != connections.end())
	{
	  assert(kt->first.first == kt->second->id2()
		 && kt->first.second == kt->second->inIndex());
			
	  if (dumbo)
	    dumbo->modulesConnected(kt->second->id1(), kt->second->outIndex(),
				    kt->second->id2(), kt->second->inIndex());
			
	  if (smartAss)
	    smartAss->modulesConnected(graphID,kt->second->id1(),
				       kt->second->outIndex(),
				       kt->second->id2(),
				       kt->second->inIndex());
	  ++kt;
	}	
    }
	
    std::string createNewGraphID(const std::string& graphName,
				 std::map<std::string,bool>& knownGraphIDs)
    {
      // the name is a good start 
      std::string id = "IDSTART" + graphName + "ENDID";

      // make it unique with a number 
      while (knownGraphIDs.find(id) != knownGraphIDs.end())
	{
	  id += '_';
	}
      
      knownGraphIDs[id] = true;
      
      return id;
    }

    std::string createNewSnapID(const std::string& snapName,
				std::map<std::string,bool>& knownSnapIDs)
    {
      std::string id = snapName + '_';
      
      while (knownSnapIDs.find(id) != knownSnapIDs.end())
	id += '_';
      
      knownSnapIDs[id] = true;
      
      return id;
    }
    
    // sucht einen Graphen und lädt ihn nach falls nötig
    Model::GraphMap::iterator lookForGraph(const std::string& graphID,
					   Model::GraphMap& graphs,
					   const SpecMap& specs,
					   GraphFileSystem& fileSystem,
					   IModuleConstructionSmartReceiver* smartAss,
					   utils::AutoPtr<utils::ILogger>& m_logger)
    {
      Model::GraphMap::iterator it=graphs.find(graphID);
      if (it==graphs.end())
	{
	  utils::AutoPtr<Graph> graph(new Graph("noid","noname"));
	  try 
	    {
	      fileSystem.loadGraph(graphID, *graph, specs);
	    }
	  catch (std::exception& e)
	    {
	      m_logger->error("Model", e.what());
	      return graphs.end();
	    }
	  
	  graphs[graphID] = graph;
	  
	  // teilt dem renderer mit dass es den graph gibt
	  if (smartAss)
	    smartAss->newGraphCreated(graphID);
	  
	  sendGraphConstruction(*graph,0,0,0,smartAss);
	  
	  it = graphs.find(graphID);
	  
	  assert( it!=graphs.end() );
	} 
      else
	{
	  assert( it!=graphs.end() );
	}
      return it;
    }	
	
    // returns wether a graph with id graphID exists
    bool graphExists(const std::string& graphID,
                     const Model::GraphMap& graphs,
                     const GraphFileSystem& fileSystem)
    {
      Model::GraphMap::const_iterator it = graphs.find(graphID);
		
      return it != graphs.end() || fileSystem.graphExists(graphID);
    }

	
    void sendSnapShotNames(const std::string& graphID,
                           const std::string& graphName,
                           const Graph::ValueSetMap& sets,
                           IGraphNameReceiver* gnr)
    {
      for (Graph::ValueSetMap::const_iterator it = sets.begin();
           it != sets.end(); ++it)
        {
          gnr->graphExists(graphID,it->first,graphName,it->second->getName());
        }
    }


  }
	
  Model::Model(const std::string graph_path,
               utils::AutoPtr<utils::ILogger>& logger)
    : dumbo(0), smartAss(0), gnr(0),serializedGraphReceiver(0),
      dr(0), controlValueReceiver(0), m_logger(logger)
  {
    fileSystem=utils::AutoPtr<GraphFileSystem>(new GraphFileSystem(graph_path,
                                                                   m_logger));
  }

  typedef std::pair<std::pair<std::string,std::string>,
                    std::list<std::pair<std::string, std::string> > > GraphInfo;
  
  namespace
  {

    class deepSearch
    {
    public:
      bool operator()(const GraphInfo& a,const GraphInfo& b)
      {
        // dirs must be smaller than their graphs
        return (a.first.second < b.first.second);
      }
    };  

  } 
	
  void Model::updateFileSystem()
  {

    typedef std::list<GraphInfo> namesList;
    typedef std::vector<GraphInfo> namesVector;
    // get list with info about all loadable graphs in the graph dir
    namesList names = fileSystem->getNames(specs);

    // stupid workaround for vc6 
    // (list::sort does not work with predicate object):
    // use global std::sort on a vector (because random access iterators are
    // needed).
    namesVector namesV(names.size());
    std::copy(names.begin(), names.end(), namesV.begin());

    // do a deep search
    //names.sort(deepSearch());
    std::sort(namesV.begin(), namesV.end(), deepSearch());

    for (namesVector::const_iterator it = namesV.begin();
         it != namesV.end(); ++it)
      {
	std::string graphID = it->first.first;
	std::string graphName = it->first.second;

#if (ENGINE_VERBOSITY > 0)
	std::cout << "name " << graphName << " id " << graphID << std::endl;
#endif
	
	if (isDirectoryName(graphName))
	  {  
	    // load directories now
	    lookForGraph(graphID, graphs, specs, *fileSystem,
                         smartAss, m_logger);
	  }
	else
	  {
	    for (std::list<std::pair<std::string, std::string> >::const_iterator
		   snap = it->second.begin(); snap != it->second.end(); ++snap)
	      {
		if (gnr != 0)
		  gnr->graphExists(graphID, snap->first,
                                   graphName, snap->second);
		
#if (ENGINE_VERBOSITY > 0)
		std::cout << "snapshotname: " << snap->second << std::endl;
#endif
		knownGraphIDs[graphID] = true;
		knownSnapIDs[snap->first] = true;
	      }
	  }
      }
  }
	
  Model::~Model() 
  {
  }
	
  void Model::addModule(const std::string& moduleClassName)
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Model::addModule: " << "moduleClassName: " 
	      << moduleClassName << std::endl;
#endif
		
    if (editGraph == 0)
      throw std::runtime_error("No editGraph at Model::addModule()");
		
    // search the spec to the moduleClassName
    SpecMap::const_iterator it = specs.find(moduleClassName);
    if (it == specs.end())
      throw std::runtime_error("ModulClassName '" + moduleClassName +
			       "'is not registered (Model::addModule)");
		
    utils::AutoPtr<IModuleClassSpec> spec = it->second;
    // add new node in graph and use the spec the iterator points to
    int moduleID = editGraph->addModule(*spec);
		
    //TODO!!!!!!!!!!!
    try {
      // inform the other parts
      smartAss->moduleAdded(editGraph->getID(),moduleClassName,moduleID);
      dumbo->moduleAdded(moduleClassName,moduleID);
    }
    catch (std::runtime_error& e)
      {
        editGraph->deleteModule(moduleID);
        m_logger->error("Model", e.what());	
      }    
		
    if (renderedGraph == editGraph)
      {
	for (unsigned int input=0;input<spec->inputs().size();++input)
	  {
	    // update snapShot with defaultvals
	    rendererControlReceiver->setInputValue(renderedGraph->getID(),
						   moduleID,input,
						   spec->defaultValue(input));
	  }
      }
		
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }

  void Model::connectModules(int moduleID1,int outputIndex,
			     int moduleID2,int inputIndex)
  {
    editGraph->connectModules(moduleID1,outputIndex,moduleID2,inputIndex);
		
    dumbo->modulesConnected(moduleID1,outputIndex,moduleID2,inputIndex);
    smartAss->modulesConnected(editGraph->getID(),moduleID1,
			       outputIndex,moduleID2,inputIndex);
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }
	
  void Model::disconnectModules(int moduleID,int inputIndex)
  {
    editGraph->disconnectModules(moduleID,inputIndex);
    dumbo->modulesDisconnected(moduleID, inputIndex);
    smartAss->modulesDisconnected(editGraph->getID(), moduleID,inputIndex);

    // update snapShot with defaultvals
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }	
	
	
  void Model::setModuleData(int moduleID,int type,const utils::Buffer& buf)
  {
#if (ENGINE_VERBOSITY > 1)
    char* content = new char[buf.getLen()+1];
    memcpy(content, buf.getPtr(), buf.getLen());
    content[buf.getLen()] = 0;
    std::cout << "setModuleData: modid=" << moduleID
	      << ", type = " << type << " " << content << std::endl;
    delete[] content;
#endif
		
    editGraph->setModuleData(moduleID,type,buf);
		
    dr->moduleDataSet(moduleID,type,buf);
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }
	
  void Model::unSetModuleData(int moduleID,int type)
  {
#if (ENGINE_VERBOSITY > 1)
    std::cout << "unSetModuleData: modid=" << moduleID
	      << ", type = " << type <<  std::endl;
#endif
		
    editGraph->unSetModuleData(moduleID,type);
		
    dr->moduleDataUnSet(moduleID,type);
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }

  void Model::setEditGraphData(int type, const utils::Buffer& buf)
  {
#if (ENGINE_VERBOSITY > 1)
    char* content = new char[buf.getLen()+1];
    memcpy(content, buf.getPtr(), buf.getLen());
    content[buf.getLen()] = 0;
    std::cout << "setEditGraphData: type=" << type << " " 
              << content << std::endl;
    delete[] content;
#endif
		
    editGraph->setData(type, buf);
		
    gr->graphDataSet(type, buf);
  }

  void Model::unSetEditGraphData(int type)
  {
#if (ENGINE_VERBOSITY > 1)
    std::cout << "unSetEditGraphData: type=" << type << std::endl;
#endif

    editGraph->unSetData(type);

    gr->graphDataUnSet(type);
  }

  bool Model::check_for_graph_id(const std::string& graph_id)
  {
    // check if the id exists
        GraphMap::const_iterator 
      it = lookForGraph(graph_id,
			graphs,
			specs,
			*fileSystem,
			smartAss,
			m_logger);

	return it != graphs.end();
  }

  bool Model::check_for_snap_id(const std::string& graph_id,
				const std::string& snap_id)
  {
    GraphMap::const_iterator 
      it = lookForGraph(graph_id,
			graphs,
			specs,
			*fileSystem,
			smartAss,
			m_logger);

    if (it==graphs.end())
      return false;

    const Graph::ValueSetMap& valueSets = it->second->getValueSetMap();
			
    return valueSets.end() != valueSets.find(snap_id);
  }
  
  
  void Model::newGraphWithID(const std::string& graphName,
                             const std::string& graphID,
                             bool notifyAndCreate)
  {
#if (ENGINE_VERBOSITY > 1)
    std::cout << "Model::newGraphWithID( graphName = '" << graphName << "',\n"
              << "graphID = '" << graphID << "' )\n\{\n";
#endif
    // check if the name of the new graph is unique
    if (graphs.end() != std::find_if(graphs.begin(),
                                     graphs.end(),
                                     has_name(graphName)))
      throw std::runtime_error("name " + graphName + 
			       " already exists (Model::newGraph)");
    
    // check if the id is unique
    if (graphs.end() != graphs.find(graphID))
      throw std::runtime_error("id " + graphID + 
			       " already exists (Model::newGraph)");
    
    // create new graph und register it
    utils::AutoPtr<Graph> newGraph ( new Graph(graphID, graphName) );
    graphs.insert(std::make_pair(graphID, newGraph));

    if(isDirectoryName(graphName))
      { // a directory has no real snapshots
        if (notifyAndCreate)
          gnr->graphExists(graphID, graphID, graphName, "");
      }
    else
      { // create default snapshot
        if (notifyAndCreate)
          {
            std::string snapName = "default";
            newGraph->newControlValueSet(graphID, snapName);
            if (gnr != 0)
              gnr->graphExists(graphID, graphID, graphName, snapName);
          }
        
        if (smartAss != 0)
          smartAss->newGraphCreated(graphID);
      }

#if (ENGINE_VERBOSITY > 1)
    std::cout << "}\n";
#endif     
  }
	
  void Model::newGraph(const std::string& graphName)
  {
#if (ENGINE_VERBOSITY > 1)
    std::cout << "Model::newGraph( graphName = '" << graphName<< "' )\n\{\n";
#endif     
    std::string graphID = createNewGraphID(graphName, knownGraphIDs);
#if (ENGINE_VERBOSITY > 1)
    std::cout << " graphID = '" << graphID << "'; \n";
#endif     

    newGraphWithID(graphName, graphID, true);

#if (ENGINE_VERBOSITY > 1)
    std::cout << "}\n";
#endif 
  }	

  void Model::renameGraph(const std::string& graphID,
			  const std::string& newGraphName)
  {
    if (!graphExists(graphID,graphs,*fileSystem))
      throw std::runtime_error("Graph doesnt exist at "
			       "Model::renameGraph(): '" + graphID + "'");
		
    //TODO
    //    if (graphExists(newGraphName,graphs,*fileSystem))
    //      throw std::runtime_error("Graph already exists at "
    //			       "Model::renameGraph()");
		
    GraphMap::iterator it = lookForGraph(graphID,graphs,specs,*fileSystem,
					 smartAss, m_logger);
		
    utils::AutoPtr<Graph> graph = it->second;
    const Graph::ValueSetMap& valueSets = graph->getValueSetMap();
		
    graph->setName(newGraphName);
		
    for (Graph::ValueSetMap::const_iterator it2 = valueSets.begin();
	 it2 != valueSets.end(); ++it2)
      {
	std::string snapID = it2->first;
	std::string snapName = it2->second->getName();
	gnr->graphRenamed(graphID,snapID,newGraphName, snapName);
      }
		
    //    smartAss->graphRenamed(graphID,newGraphName);
		
    /*
      try {
      fileSystem->rename(graphID,newGraphName);
      }
      catch (...) {} //TODO: added, because some graphs arent on disc but
      // only exist in the model.
      */
		
  }
	
	
	
  void Model::deserializeGraph(const std::string& graphstream)
  {
    utils::AutoPtr<Graph> deserializedGraph (new Graph("noIDYet",
						       "noNameYet"));
    std::istringstream ist(graphstream);
    model::deserializeGraph(ist,*deserializedGraph,specs, *m_logger);
    //ist >> (*deserializedGraph);
    // is there already a graph with that id?
    const std::string id = deserializedGraph->getID();
    GraphMap::const_iterator it = graphs.find(id);
    if (it == graphs.end())
      { // this name doesn't exist
	graphs[id]=deserializedGraph;
	smartAss->newGraphCreated(id);
	//TODO snapshots an graphnamereceiver schicken
      }
    else
      {
#if (ENGINE_VERBOSITY > 0)
	std::cout << "deserialize to existig graph!!!!\n";
#endif
	// TODO
      }
  }
	
  void Model::serializeGraph(const std::string& graphID)
  {
    std::ostringstream graphStream;
		
    GraphMap::const_iterator i = graphs.find(graphID);
    if (i == graphs.end()) {
      throw std::runtime_error("unknown graphname(Model::serializeGraph)");
    }
		
    graphStream << *((*i).second);
    const std::string serializedGraph = graphStream.str();
    serializedGraphReceiver->graphSerialized(graphID,serializedGraph);
  }
	
  void Model::synchronize()// editgraph
  {
    dr->syncDataStarted();
    gr->syncGraphDataStarted();
    dumbo->syncModuleStarted();
	
    sendExistingGraphs();

    if (editGraph)
      {
        modelStatusReceiver->editGraphChanged(editGraph->getID(),
                                              editControlSet->getID());
      }

    sendGraphConstruction(*editGraph,dumbo,dr, gr);
	
		
    dumbo->syncModuleFinished();
    dr->syncDataFinished();
    gr->syncGraphDataFinished();
  }

  void Model::sendExistingGraphs()
  {
    // first send those graphs that are in memory
    for (GraphMap::const_iterator it = graphs.begin();
         it != graphs.end(); ++it)
      {
        utils::AutoPtr<Graph> current = it->second;
        std::string graphID   = current->getID();
        std::string graphName = current->getName();
		  
        const Graph::ValueSetMap value_sets = current->getValueSetMap();
        for (Graph::ValueSetMap::const_iterator valit = value_sets.begin();
             valit != value_sets.end(); ++valit)
          {
            Graph::ControlValueSetPtr current = valit->second;
            std::string snapID = current->getID();
            std::string snapName = current->getName();
			  
            gnr->graphExists(graphID, snapID, graphName, snapName);
          }
      }

    // now send the graphs that are on disc but *not* in memory
	  
    typedef std::list<GraphInfo> namesList;
    typedef std::vector<GraphInfo> namesVector;
    // get list with info about all loadable graphs in the graph dir
    namesList names = fileSystem->getNames(specs);
	  
    // stupid workaround for vc6 
    // (list::sort does not work with predicate object):
    // use global std::sort on a vector (because random access iterators are
    // needed).
    namesVector namesV(names.size());
    std::copy(names.begin(), names.end(), namesV.begin());
	  
    // do a deep search
    //names.sort(deepSearch());
    std::sort(namesV.begin(), namesV.end(), deepSearch());
	  
    for (namesVector::const_iterator it = namesV.begin();
         it != namesV.end(); ++it)
      {
        std::string graphID = it->first.first;
        std::string graphName = it->first.second;
		  
        if (isDirectoryName(graphName))
          {  
            // load directories now
            lookForGraph(graphID,graphs,specs,*fileSystem,smartAss, m_logger);
          }
        else
          {
            for (std::list<std::pair<std::string, std::string> >::const_iterator
                   snap = it->second.begin(); snap != it->second.end(); ++snap)
              {
                if (gnr != 0 && graphs.find(graphID) == graphs.end())
                  gnr->graphExists(graphID,snap->first,
                                   graphName, snap->second);
              }
          }
      }
  }
	
  void Model::moduleClassLoaded(const std::string& moduleClassName,
				const IModuleClassSpec& spec)
  {
    SpecMap::const_iterator it = specs.find(moduleClassName);
		
    if (it != specs.end())
      throw std::runtime_error("modulclassname already exists(Model::moduleClassLoaded)");
		
    specs[moduleClassName] = utils::AutoPtr<IModuleClassSpec>(spec.clone());

#if (ENGINE_VERBOSITY > 0)
    std::cout << "loaded moduleclass: " <<  moduleClassName << std::endl;
#endif
  }
	
  void Model::moduleClassUnloaded(const std::string& moduleClassName)
  {
    SpecMap::iterator it = specs.find(moduleClassName);
    if (it == specs.end())
      throw std::runtime_error("moduleclasse doesnt exist (Model::moduleClassUnloaded)");
		
    // alle Module dieser Klasse in allen Graphen löschen
    for (GraphMap::const_iterator graphIt =
	   graphs.begin(); graphIt != graphs.end(); ++graphIt)
      {
	utils::AutoPtr<Graph> current = graphIt->second;
			
	Graph::GraphNodeList nodes = current->nodes();
	for (Graph::GraphNodeList::const_iterator nodeIt = nodes.begin();
	     nodeIt != nodes.end(); ++nodeIt)
	  {
	    utils::AutoPtr<GraphNode> node = *nodeIt;
	    if (node->spec().moduleClassName() == moduleClassName)
	      {
		this->deleteModule(current, node->moduleID());
	      }
	  }
      }
		
    specs.erase(it);	
#if (ENGINE_VERBOSITY > 0)
    std::cout << "unloaded moduleclass: " <<  moduleClassName << std::endl;
#endif
  }
	
  void Model::controlValueChanged(const std::string& graphID,
				  int nodeID,int inputIndex,
				  const utils::Buffer& newValue) // Renderer
  {
    GraphMap::const_iterator it = graphs.find(graphID);
    if (it == graphs.end())
      {
	// TODO try to load graph from disc
        m_logger->error("Model",
                        "graphID doesnt exist (controlValueChanged)");
        return;
      }
		
    //TODO: ich glaub das ist ein fehler: der wert gehoert
    // nicht unbedingt ins renderedControlSet
    // (falls er z.B. bei syncInputValue getriggert wurde)
    /*if (renderedControlSet)
      renderedControlSet->setControlValue(nodeID,inputIndex,newValue);*/
		
    if (editGraph == renderedGraph && editControlSet == renderedControlSet)
      {
	controlValueReceiver->controlValueChanged(nodeID, inputIndex,
						  newValue);
      }
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }
	
  void Model::syncInputValuesStarted(const std::string& /*graphID*/)
  {
    //TODO
  }
	
  void Model::syncInputValuesFinished(const std::string& /*graphID*/)
  {
    //TODO
  }
	
	
  void Model::registerModuleConstructionDumbReceiver(IModuleConstructionDumbReceiver& r)
  {
    dumbo = &r;
  }
	
  void Model::registerModuleConstructionSmartReceiver(IModuleConstructionSmartReceiver& r)
  {
    smartAss = &r;
  }
	
  void Model::registerControlValueReceiver(IControlValueReceiver& r)
  {
    controlValueReceiver=&r;
  }
	
  void Model::registerGraphNameReceiver(IGraphNameReceiver& r)
  {
    gnr = &r;
  }

  void Model::registerModuleDataReceiver(IModuleDataReceiver& r)
  {
    dr = &r;
  }

  void Model::registerGraphDataReceiver(IGraphDataReceiver& r)
  {
    gr = &r;
  }
	
  void Model::registerSerializedGraphReceiver(ISerializedGraphReceiver& r)
  {
    serializedGraphReceiver = &r;
  }
	
  void Model::registerRendererControlReceiver(IRendererControlReceiver& r)
  {
    rendererControlReceiver = &r;
  }
	
  void Model::registerModelStatusReceiver(IModelStatusReceiver& r)
  {
    modelStatusReceiver = &r;
  }
	
  void Model::changeRenderedGraph(const std::string& graphID,
				  const std::string& snapID)
  {		
    // check if graph has changed
    if (renderedGraph == 0 || graphID != renderedGraph->getID() ||
	snapID != renderedControlSet->getID())
      {
	GraphMap::const_iterator 
	  it = lookForGraph(graphID,
                            graphs,
                            specs,
                            *fileSystem,
                            smartAss,
                            m_logger);

	if (it==graphs.end())
	  {	    
	    throw std::runtime_error("graphID doesnt exist "
				     "(Model::changeRenderedGraph)");
	  }

	renderedGraph = it->second;

	smartAss->graphChanged(graphID);

	const Graph::ValueSetMap& valueSets = renderedGraph->getValueSetMap();
			
	Graph::ValueSetMap::const_iterator valIt = valueSets.find(snapID);
			
	if (valIt == valueSets.end())
	  {
	    throw std::runtime_error("No such snapShot at "
				     "Model::changeRenderedGraph()");
	  }

	renderedControlSet = valIt->second;

        typedef std::list<std::pair<int, int> > InputList;
	InputList del_list;

	for (ControlValueSet::const_iterator
	       setIt = renderedControlSet->begin();
             setIt!=renderedControlSet->end(); ++setIt)
          {
            int moduleID   = setIt->first.first;
            int inputIndex = setIt->first.second;
            try
              {
                rendererControlReceiver->setInputValue(graphID,
                                                       moduleID,
                                                       inputIndex,
                                                       setIt->second);
              }
            catch (std::runtime_error& e)
              {
                std::ostringstream os;
                os << e.what() << "\n";
                os << "Removing value of module " << moduleID
                   << ", input " << inputIndex << " from snapshot.\n";
                os << "Save this graph to make the removal permanent.\n";
                os << "Note: this message means that the graph "
                   << "has become corrupted\n(i.e. does not fit to the "
                   << "interface of the used modules).\n";
                os << "This could mean that the graph was created with "
                   << "a different version of GePhex.\n";
                m_logger->error("Model", os.str());
			
                // remember the node and delete later
                del_list.push_back(setIt->first);
              }
          }

	// delete invalid entries from snapshot
	for (InputList::const_iterator it = del_list.begin();
             it != del_list.end(); ++it)
          {
            renderedControlSet->deleteControlValue(it->first, it->second);
          }

      }
  }

  void Model::newControlValueSet(const std::string& graphID,
                                 const std::string& snapName)
  {
    std::string snapID = createNewSnapID(snapName,knownSnapIDs);
    newControlValueSetWithID(graphID, snapName, snapID);
  }

  void Model::newControlValueSetWithID(const std::string& graphID,
                                       const std::string& snapName,
                                       const std::string& snapID)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss, m_logger);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::newControlValueSet()");
		
    
    it->second->newControlValueSet(snapID, snapName);
		
    gnr->graphExists(graphID, snapID, it->second->getName(), snapName);
  }
	
  void Model::renameControlValueSet(const std::string& graphID,
                                    const std::string& snapID,
                                    const std::string& newSnapName)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss, m_logger);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::renameControlValueSet()");
		
    it->second->renameControlValueSet(snapID, newSnapName);
		
    gnr->graphRenamed(graphID, snapID, it->second->getName(), newSnapName);
  }
	
  void Model::copyControlValueSet(const std::string& graphID,
                                  const std::string& snapID,
                                  const std::string& newSnapName)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss, m_logger);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::copyControlValueSet()");
		
    std::string newID = createNewSnapID(newSnapName,knownSnapIDs);
    it->second->copyControlValueSet(snapID, newID, newSnapName);
		
    gnr->graphExists(graphID, newID, it->second->getName(),newSnapName);
  }
	
  void Model::deleteControlValueSet(const std::string& graphID,
                                    const std::string& snapID)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss, m_logger);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::deleteControlValueSet()");
		
    it->second->deleteControlValueSet(snapID);
		
    gnr->graphNoLongerExists(graphID, snapID);
		
    if (it->second->getValueSetMap().empty())
      {
	this->deleteGraph(graphID);
      }
  }
	
	
  void Model::deleteModule(utils::AutoPtr<Graph> current, int moduleID)
  {
    const Graph::ConnectionMap&
      connections = current->connections();
		
    Graph::ConnectionMap::const_iterator  it = connections.begin();
		
    std::list<std::pair<int,int> > delList;
		
    while(it != connections.end())
      {
	utils::AutoPtr<GraphConnection> conn = it->second;
	if(conn->id1() == moduleID || conn->id2() == moduleID)
	  {
	    delList.push_back(it->first);
	  }
	++it;
      }
		
    for (std::list<std::pair<int,int> >::const_iterator kt = delList.begin();
	 kt != delList.end(); ++kt)
      {
	current->disconnectModules(kt->first,kt->second);
	if (current == editGraph)
	  dumbo->modulesDisconnected(kt->first,kt->second);
	smartAss->modulesDisconnected(current->getID(),kt->first,kt->second);
      }
		
    std::list<int> moduleDataList = current->moduleDataList(moduleID);
    for (std::list<int>::const_iterator xt = moduleDataList.begin();
	 xt != moduleDataList.end(); ++xt)
      {
	if (current == editGraph)
	  dr->moduleDataUnSet(moduleID,*xt);
      }
		
    current->deleteModule(moduleID);
		
    if (current == editGraph)
      dumbo->moduleDeleted(moduleID);
		
    smartAss->moduleDeleted(current->getID(),moduleID);
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }
	
  void Model::deleteModule(int moduleID)
  {
    deleteModule(editGraph, moduleID);
		
#ifndef NDEBUG
    //checkGraphSerialisation();
#endif
  }
  

  void Model::saveGraph(const std::string& graphID)
  {
    GraphMap::const_iterator 
      it = lookForGraph(graphID,graphs,specs,*fileSystem,smartAss,
                        m_logger);

    if (it == graphs.end())
      throw std::runtime_error("(Model::saveGraph) no graph with id: "
			       + graphID);
    
    // save the dirs
    std::string graphName = (*it).second->getName();
    
    // extract the names of all subdirs
    for(std::string::iterator strit=graphName.begin();
	strit!=graphName.end();
	++strit)
      {
	if ( *strit=='/' && strit!=graphName.begin() )
	  {
	    std::string dir(graphName.begin(),strit+1);
	    // dir is the name of the subdir

	    // search the graphid by name
	    GraphMap::const_iterator dirIt = std::find_if(graphs.begin(),
							  graphs.end(),
							  has_name(dir)
							  );
	    if (dirIt != graphs.end() )
	      {
		fileSystem->saveGraph(*dirIt->second);
	      }
	    else
	      {
                std::ostringstream os;
		os << "graph "<< graphName <<" is in a unknown directory with the name";
		os << " : " << dir;
		m_logger->error("Model", os.str());
	      }
	  }
      }
    
    // and now save the the graph
    fileSystem->saveGraph(*it->second);
  }
  
  void Model::deleteGraph(const std::string& graphID)
  {
	  
    GraphMap::iterator it = graphs.find(graphID);
	  
    if (it != graphs.end())  // is the graph loaded?
      {
        if (editGraph->getID() == graphID)
          {
            sendGraphDestruction(*editGraph, *dumbo, *dr, *gr);
            editGraph = utils::AutoPtr<Graph>(0);
          }

        utils::AutoPtr<Graph> g = it->second;
        graphs.erase(it);    
		  
        smartAss->graphDeleted(graphID);
        fileSystem->deleteGraph(graphID);
		  
        if (isDirectoryName(g->getName()))
          {
            gnr->graphNoLongerExists(graphID,"");
            // delete all graphs in that dir
			  
            // TODO
          }
        else
          {
            const Graph::ValueSetMap& vals = g->getValueSetMap();
            for (Graph::ValueSetMap::const_iterator valIt = vals.begin();
                 valIt != vals.end(); ++valIt)
              {		
                gnr->graphNoLongerExists(graphID, valIt->first);
              }
          } 		  
      }
    else // graph is not loaded
      {	
        if (!fileSystem->graphExists(graphID))
          throw std::runtime_error("(Model::deleteGraph) no graphid: "+ graphID);
	  
        GraphFileSystem::ValueSetList valueSetList 
          = fileSystem->getValueSetList(graphID);
        if (valueSetList.empty())
          gnr->graphNoLongerExists(graphID, "");
        else
	  {
            for (GraphFileSystem::ValueSetList::const_iterator it = valueSetList.begin();
	         it != valueSetList.end(); ++it)
              {
                gnr->graphNoLongerExists(graphID, it->first);
              }
	  }

        fileSystem->deleteGraph(graphID);
      }
  }

  void Model::changeEditGraph(const std::string& graphID,
			      const std::string& snapID)
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Model::changeEditGraph(" << graphID << ", " << snapID <<")"
	      << std::endl;
#endif
		
    GraphMap::const_iterator 
      it = lookForGraph(graphID,graphs,specs,*fileSystem, smartAss, m_logger);
		
    if (it == graphs.end())
      {
	m_logger->error("Model", "Could not change to Graph");
        return;
      }

    modelStatusReceiver->editGraphChanged(graphID, snapID);

    if (editGraph != it->second || snapID != editControlSet->getID())
      {
	if (editGraph != it->second)
	  {
	    if (editGraph != 0)
	      {
		sendGraphDestruction(*editGraph, *dumbo, *dr, *gr);
	      }
								
	    editGraph=it->second;				
	    sendGraphConstruction(*editGraph, dumbo, dr, gr);
	  }
	
	const Graph::ValueSetMap& valueSets = editGraph->getValueSetMap();
	
	Graph::ValueSetMap::const_iterator valIt = valueSets.find(snapID);
	
	if (valIt == valueSets.end())
	  {
	    throw std::runtime_error("No such snapShot at "
				     "Model::changeEditGraph()");
	  }
	
	editControlSet= valIt->second;
	
	for (ControlValueSet::const_iterator
	       setIt = editControlSet->begin();
	     setIt != editControlSet->end(); ++setIt)
	  {
	    controlValueReceiver->controlValueChanged(setIt->first.first,
						      setIt->first.second,
						      setIt->second);
	  }
	
      }
		
  }
	
  void Model::setInputValue(int moduleID, int inputIndex,
			    const utils::Buffer& buf)
  {		
    editControlSet->setControlValue(moduleID, inputIndex, buf);
			
    if (editGraph == renderedGraph && editControlSet == renderedControlSet)
      {
	rendererControlReceiver->setInputValue(editGraph->getID(),moduleID,
					       inputIndex, buf);
      }
    else
      {
        //only needed explicitly here, because the renderer notifies
        //the controlValuereceiver in the upper branch
        controlValueReceiver->controlValueChanged(moduleID,inputIndex,buf);
      }
		
  }
	
  void Model::syncInputValue(int moduleID, int inputIndex)
  {
		
    ControlValueSet::const_iterator
      it = editControlSet->find(std::make_pair(moduleID,inputIndex));
		
    if (it == editControlSet->end())
      {
	/*rendererControlReceiver->syncInputValue(editGraph->getName(),
	  moduleID, inputIndex);*/
			
	//TODO
	//it = editControlSet->values.find(std::make_pair(moduleID,
        //	 inputIndex));
			
	//if (it == editControlSet->values.end())
	{			
	  //throw std::runtime_error("Mist bei Model::syncInputValue()");
          m_logger->error("Model", "Mist bei Model::syncInputValue()");
	}		
      }
    else
      {
			
	controlValueReceiver->controlValueChanged(moduleID, inputIndex,
						  it->second);
      }
		
  }
	
  void Model::copyGraph(const std::string& srcGraphID,
			const std::string& dstGraphName)
  {
    GraphMap::const_iterator src 
      = lookForGraph(srcGraphID,graphs,specs,*fileSystem,smartAss,m_logger);
		
    if (src == graphs.end())
      {
	throw std::runtime_error("No such Graph at "
				 "Model::copyGraph()");
      }
		
    //TODO
    /*    GraphMap::const_iterator 
	  dst = lookForGraph(dstGraphName,graphs,specs,*fileSystem,smartAss);
	  if (dst == graphs.end())
	  {
	  newGraph(dstGraphName);
	  dst = graphs.find(dstGraphName);
	  }*/
		
		
    std::string newID = createNewGraphID(dstGraphName, knownGraphIDs);
		
    newGraphWithID(dstGraphName, newID, false);
		
    GraphMap::const_iterator dst = graphs.find(newID);
    assert ( dst != graphs.end() );

    std::ostringstream ostSrc;
    ostSrc << *src->second;
    std::string serSrc = ostSrc.str();
    std::istringstream ist(serSrc);
    model::deserializeGraph(ist, *(dst->second),specs,*m_logger);
    dst->second->setName(dstGraphName);
    dst->second->setID(newID);
		
    sendGraphConstruction(*dst->second,0,0,0,smartAss);
    sendSnapShotNames(newID,dstGraphName,dst->second->getValueSetMap(),gnr);
  }
	
  void Model::modExecTimeSignal(const std::string& graphID,
				int nodeID, double execTime)
  {
    if (editGraph != 0 && graphID == editGraph->getID())
      moduleStatisticsReceiver->modExecTimeSignal(nodeID,execTime);
  }
	
  void Model::registerModuleStatisticsReceiver(IModuleStatisticsReceiver& r)
  {
    moduleStatisticsReceiver = &r;
  }
	
	
#ifndef NDEBUG
  void Model::checkGraphSerialisation(){
    std::ostringstream ostOld;
    ostOld << *editGraph;
    std::string serOld = ostOld.str();
#if (ENGIN_VERBOSITY > 0)
    std::cout << "------------original-graph-------------\n";
    std::cout << serOld << std::endl;
#endif
    std::istringstream ist(serOld);
    //Graph builtGraph(0, specs,"blahblah");
    Graph builtGraph("blahblah","blohbloh");
    model::deserializeGraph(ist, builtGraph,specs, *m_logger);
    //ist >> builtGraph;
#if (ENGIN_VERBOSITY > 0)
    std::cout << "------------reloaded-graph-------------\n";
		
    std::cout << (builtGraph) << std::endl;
#endif		
		
    std::ostringstream ostNew;
    ostNew << builtGraph;
    std::string serNew = ostNew.str();
#if (ENGIN_VERBOSITY > 0)
    if (serOld==serNew)
      {
	std::cout << "------------identical------------------\n";
      }
    else
      {
	std::cout << "----!!!!!!--not identical--!!!!!!!-----\n";
      }
#endif
  }
#endif
	
	
}
