#include "model.h"

#include <ctime>

#include <list>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <sstream>

#include "graph.h"
#include "graphserial.h"
#include "graphnode.h"
#include "graphconnection.h"
#include "graphfilesystem.h"

#include "utils/autoptr.h"

#include "interfaces/igraphnamereceiver.h"
#include "interfaces/imoduleconstructionsmartreceiver.h"
#include "interfaces/imoduleconstructiondumbreceiver.h"
#include "interfaces/imoduledatareceiver.h"
#include "interfaces/iserializedgraphreceiver.h"
#include "interfaces/irenderercontrolreceiver.h"

#include "interfaces/imoduleclassspec.h"
#include "interfaces/icontrolvaluereceiver.h"
#include "interfaces/imodulestatisticsreceiver.h"
#include "interfaces/imodelstatusreceiver.h"

#include "controllvalueset.h"

	

namespace model
{

  namespace
  {
    // Teilt einem IModuleConstructionDumbReceiver mit, dass alle Module
    // und Connections eines Graphen gelöscht wurden.
    void sendGraphDestruction(const Graph& g,
			      IModuleConstructionDumbReceiver& dumbo,
			      IModuleDataReceiver& dr)
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
			       IModuleConstructionSmartReceiver* smartAss = 0)
    {
      const std::string graphID = g.getID();
      const Graph::GraphNodeList& nodes = g.nodes();
		
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
			
	  const std::map<int,utils::Buffer>& datas = (*jt)->data();
	  for (std::map<int,utils::Buffer>::const_iterator lt = datas.begin();
	       lt != datas.end(); ++lt)
	    {
	      if (dr)
		dr->moduleDataSet((*jt)->moduleID(), lt->first,
				  lt->second);
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
      //TODO
      /*time_t tt = time(0);
      std::string time = ctime(&tt);
      return time;*/
      std::string id = graphName + '_';

      while (knownGraphIDs.find(id) != knownGraphIDs.end())
	id += '_';

      knownGraphIDs[id] = true;
      return id;
    }

    std::string createNewSnapID(const std::string& snapName,
				std::map<std::string,bool>& knownSnapIDs)
    {
      //TODO
      /*time_t tt = time(0);
      std::string time = ctime(&tt);
      return time;*/
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
					   IModuleConstructionSmartReceiver* smartAss)
    {
      Model::GraphMap::iterator it=graphs.find(graphID);
    if (it==graphs.end())
      {
	utils::AutoPtr<Graph> graph(new Graph("noid","noname"));
	try {
	  fileSystem.loadGraph(graphID, *graph, specs);
	}
	catch (std::runtime_error& e)
	  {
	    std::cerr << e.what() << std::endl;
	    return graphs.end();
	  }
			
	graphs[graphID] = graph;
			
	// teilt dem renderer mit dass es den graph gibt
	if (smartAss)
	  smartAss->newGraphCreated(graphID);
			
	sendGraphConstruction(*graph,0,0,smartAss);
			
	it = graphs.find(graphID);
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
	
  Model::Model(const std::string basepath_)
    : dumbo(0), smartAss(0), gnr(0),serializedGraphReceiver(0),
      dr(0),controlValueReceiver(0)
  {
    fileSystem=utils::AutoPtr<GraphFileSystem>(new GraphFileSystem(basepath_));								   
  }
	
  void Model::updateFileSystem()
  {
    typedef const std::list<std::pair<std::pair<std::string,std::string>,std::list<std::pair<std::string, std::string> > > > namesList;
    namesList names = fileSystem->getNames(specs);
		
    for (namesList::const_iterator it = names.begin();it != names.end(); ++it)
      {
	std::string graphID = it->first.first;
	std::string graphName = it->first.second;

#if (ENGINE_VERBOSITY > 0)
	std::cout << "graphname: " << graphName << "  " << std::endl;
#endif
			
	for (std::list<std::pair<std::string, std::string> >::const_iterator
	       snap = it->second.begin(); snap != it->second.end(); ++snap)
	  {
	    if (gnr != 0)
	      gnr->graphExists(graphID,snap->first, graphName, snap->second);

#if (ENGINE_VERBOSITY > 0)
	    std::cout << "snapshotname: " << snap->second << std::endl;
#endif
	    knownGraphIDs[graphID] = true;
	    knownSnapIDs[snap->first] = true;
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
    catch (std::runtime_error&)
      {
	editGraph->deleteModule(moduleID);
	throw;
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
	
  void Model::newGraphWithID(const std::string& graphName,
			     const std::string& graphID)
  {
    for (GraphMap::const_iterator git = graphs.begin();
	 git != graphs.end(); ++git)
      {
	if (git->second->getName() == graphName)
	  {
	    throw std::runtime_error("a graph with that name (" + graphName +
				     ") already exists (Model::newGraph)");
	  }
      }
		
    GraphMap::const_iterator it = graphs.find(graphID);
    assert( it == graphs.end() );
		
    utils::AutoPtr<Graph> newGraph(new Graph(graphID,graphName));
    graphs[graphID]=newGraph;
		
    std::string snapName = "default";
    newGraph->newControlValueSet(graphID,snapName);
		
    if (gnr != 0)
      gnr->graphExists(graphID,graphID,graphName,snapName);
		
    smartAss->newGraphCreated(graphID);
  }
	
  void Model::newGraph(const std::string& graphName)
  {        
    std::string id = createNewGraphID(graphName, knownGraphIDs);
		
    newGraphWithID(graphName, id);
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
					 smartAss);
		
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
    model::deserializeGraph(ist,*deserializedGraph,specs);
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
    dumbo->syncModuleStarted();
		
    sendGraphConstruction(*editGraph,dumbo,dr);
		
    dumbo->syncModuleFinished();
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
	throw std::runtime_error("graphID doesnt exist"
				 "(Model::controlValueChanged)");
      }
		
    //TODO: ich glaub das ist ein fehler: der wert gehoert
    // nicht unbedingt ins renderedControllSet
    // (falls er z.B. bei syncInputValue getriggert wurde)
    /*if (renderedControllSet)
      renderedControllSet->setControlValue(nodeID,inputIndex,newValue);*/
		
    if (editGraph == renderedGraph && editControllSet == renderedControllSet)
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
	snapID != renderedControllSet->getID())
      {
	GraphMap::const_iterator 
	  it = lookForGraph(graphID,graphs,specs,*fileSystem, smartAss);

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

	renderedControllSet = valIt->second;

	for (ControllValueSet::const_iterator
	       setIt = renderedControllSet->begin();
	     setIt!=renderedControllSet->end();++setIt)
	  {
	    rendererControlReceiver->setInputValue(graphID,
						   setIt->first.first,
						   setIt->first.second,
						   setIt->second);
	  }
      }
  }
	
  void Model::newControllValueSet(const std::string& graphID,
				  const std::string& snapName)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::newControllValueSet()");
		
    std::string snapID = createNewSnapID(snapName,knownSnapIDs);
    it->second->newControlValueSet(snapID, snapName);
		
    gnr->graphExists(graphID, snapID, it->second->getName(), snapName);
  }
	
  void Model::renameControllValueSet(const std::string& graphID,
				     const std::string& snapID,
				     const std::string& newSnapName)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::renameControllValueSet()");
		
    it->second->renameControllValueSet(snapID, newSnapName);
		
    gnr->graphRenamed(graphID,snapID,it->second->getName(),newSnapName);
  }
	
  void Model::copyControllValueSet(const std::string& graphID,
				   const std::string& snapID,
				   const std::string& newSnapName)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::copyControllValueSet()");
		
    std::string newID = createNewSnapID(newSnapName,knownSnapIDs);
    it->second->copyControllValueSet(snapID, newID, newSnapName);
		
    gnr->graphExists(graphID, newID, it->second->getName(),newSnapName);
  }
	
  void Model::deleteControllValueSet(const std::string& graphID,
				     const std::string& snapID)
  {
    GraphMap::const_iterator it = lookForGraph(graphID,graphs,specs,
					       *fileSystem,smartAss);
		
    if (it == graphs.end())
      throw std::runtime_error("No such Graph at "
			       "Model::deleteControllValueSet()");
		
    it->second->deleteControllValueSet(snapID);
		
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
    GraphMap::const_iterator it = graphs.find(graphID);
    if (it == graphs.end())
      throw std::runtime_error("no graph with that id (Model::saveGraph): "
			       + graphID);
    fileSystem->saveGraph(*it->second);
  }
	
  void Model::deleteGraph(const std::string& graphID)
  {
		
    GraphMap::iterator it = lookForGraph(graphID, graphs, specs,
					 *fileSystem, 0);
		
    if ( it == graphs.end() )
      {					
	throw std::runtime_error("Musterbeispiel: " + graphID);
      }
		
    utils::AutoPtr<Graph> g = it->second;
    graphs.erase(it);
		
    fileSystem->deleteGraph(graphID);
		
    const Graph::ValueSetMap& vals = g->getValueSetMap();
		
    for (Graph::ValueSetMap::const_iterator valIt = vals.begin();
	 valIt != vals.end(); ++valIt)
      {		
	gnr->graphNoLongerExists(graphID, valIt->first);
      }

    smartAss->graphDeleted(graphID);
  }

  void Model::changeEditGraph(const std::string& graphID,
			      const std::string& snapID)
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Model::changeEditGraph(" << graphID << ", " << snapID <<")"
	      << std::endl;
#endif
		
    GraphMap::const_iterator 
      it = lookForGraph(graphID,graphs,specs,*fileSystem, smartAss);
		
    if (it == graphs.end())
      {
	throw std::runtime_error("Could not change to Graph");
      }      
		
    if (editGraph != it->second || snapID != editControllSet->getID())
      {
	if (editGraph != it->second)
	  {
	    if (editGraph != 0)
	      {
		sendGraphDestruction(*editGraph, *dumbo, *dr);
	      }
				
				
	    editGraph=it->second;
				
	    sendGraphConstruction(*editGraph, dumbo, dr);
				
	  }
	
	const Graph::ValueSetMap& valueSets = editGraph->getValueSetMap();
	
	Graph::ValueSetMap::const_iterator valIt = valueSets.find(snapID);
	
	if (valIt == valueSets.end())
	  {
	    throw std::runtime_error("No such snapShot at "
				     "Model::changeEditGraph()");
	  }
	
	editControllSet= valIt->second;
	
	for (ControllValueSet::const_iterator
	       setIt = editControllSet->begin();
	     setIt != editControllSet->end(); ++setIt)
	  {
	    controlValueReceiver->controlValueChanged(setIt->first.first,
						      setIt->first.second,
						      setIt->second);
	  }

	modelStatusReceiver->editGraphChanged(graphID, snapID);
      }
		
  }
	
  void Model::setInputValue(int moduleID, int inputIndex,
			    const utils::Buffer& buf)
  {		
    editControllSet->setControlValue(moduleID, inputIndex, buf);
			
    if (editGraph == renderedGraph && editControllSet == renderedControllSet)
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
		
    ControllValueSet::const_iterator
      it = editControllSet->find(std::make_pair(moduleID,inputIndex));
		
    if (it == editControllSet->end())
      {
	/*rendererControlReceiver->syncInputValue(editGraph->getName(),
	  moduleID, inputIndex);*/
			
	//TODO
	//it = editControllSet->values.find(std::make_pair(moduleID,
	//													 inputIndex));
			
	//if (it == editControllSet->values.end())
	{			
	  throw std::runtime_error("Mist bei Model::syncInputValue()");
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
      = lookForGraph(srcGraphID,graphs,specs,*fileSystem,smartAss);
		
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
		
		
    std::string newID = createNewGraphID(dstGraphName,knownGraphIDs);
		
    newGraphWithID(dstGraphName, newID);
		
    GraphMap::const_iterator dst = graphs.find(newID);
    assert ( dst != graphs.end() );
		
		
    std::ostringstream ostSrc;
    ostSrc << *src->second;
    std::string serSrc = ostSrc.str();
    std::istringstream ist(serSrc);
    model::deserializeGraph(ist, *(dst->second),specs);		
    dst->second->setName(dstGraphName);
    dst->second->setID(newID);
		
    sendGraphConstruction(*dst->second,0,0,smartAss);
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
    std::cout << "------------original-graph-------------\n";
    std::cout << serOld << std::endl;
    std::istringstream ist(serOld);
    //Graph builtGraph(0, specs,"blahblah");
    Graph builtGraph("blahblah","blohbloh");
    model::deserializeGraph(ist, builtGraph,specs);
    //ist >> builtGraph;
    std::cout << "------------reloaded-graph-------------\n";
		
    std::cout << (builtGraph) << std::endl;
		
		
    std::ostringstream ostNew;
    ostNew << builtGraph;
    std::string serNew = ostNew.str();
    if (serOld==serNew)
      {
	std::cout << "------------identical------------------\n";
      }
    else
      {
	std::cout << "----!!!!!!--not identical--!!!!!!!-----\n";
      }
  }
#endif
	
	
}
