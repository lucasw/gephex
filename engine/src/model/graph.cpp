#include "graph.h"

#include <stdexcept>
#include <iostream>

#include "graphconnection.h"
#include "graphnode.h"

#include "interfaces/imoduleclassspec.h"

#include "controllvalueset.h"

namespace model
{
  Graph::Graph(const std::string& id_, const std::string& name_)
    : m_id(id_), m_name(name_),m_maxModuleID(0)/*, m_specs(spec_)*/
  {
  }

  Graph::~Graph()
  {   
  }


  void Graph::addModule(const IModuleClassSpec& spec, int moduleID)
  {	
    if (moduleID > m_maxModuleID)
      m_maxModuleID = moduleID;

    utils::AutoPtr<GraphNode> 
      newNode ( new GraphNode(spec,moduleID) );

    m_nodes.push_back( newNode );

    // add all default controll values to snapshots
    for (unsigned int input=0;input<spec.inputs().size();++input)
      {
	// all snapshots
	for (Graph::ValueSetMap::iterator i=valueSets.begin();i!=valueSets.end();++i)
	  {
	    i->second->setControlValue(moduleID,input,spec.defaultValue(input));
	  }
      }
  }


  void Graph::connectModules(int moduleID1,int outputIndex,
			     int moduleID2,int inputIndex)
  {
    // get GraphNodes from ID
    utils::AutoPtr<GraphNode> gn1 ( 0 ); // no sender yet found
    utils::AutoPtr<GraphNode> gn2 ( 0 ); // no receiver yet found
    for (GraphNodeList::iterator i = m_nodes.begin();i != m_nodes.end(); ++i)
      {
	if ((*i)->moduleID()==moduleID1) // found sender
	  gn1=(*i);
    	if ((*i)->moduleID()==moduleID2) // found receiver
	  gn2=(*i);
    	if (gn1 && gn2)
	  break;
      }

    if (gn1 == 0 || gn2 == 0)
      throw std::runtime_error("there is no modul with this id(graph::connect)");

    const IModuleClassSpec& spec1 = gn1->spec();
    const IModuleClassSpec& spec2 = gn2->spec();

    if (outputIndex < 0 || outputIndex >= (int) spec1.outputs().size()
	|| inputIndex < 0 || inputIndex >= (int) spec2.inputs().size())
      throw std::runtime_error("Index out of range at Graph::connectModules()");

    ConnectionMap::const_iterator 
      it = m_connections.find(std::make_pair(moduleID2,inputIndex));
    if (it != m_connections.end())
      throw std::runtime_error("Input ist schon verbunden bei connect!");

    utils::AutoPtr<GraphConnection> 
      newConnection ( new GraphConnection(moduleID1,outputIndex,
					  moduleID2,inputIndex) );

    m_connections[std::make_pair(moduleID2,inputIndex)] = newConnection;
  }


  void Graph::disconnectModules(int moduleID,int inputIndex)
  {
    ConnectionMap::iterator it = m_connections.find(std::make_pair(moduleID,
								   inputIndex));

    if (it == m_connections.end())
      throw std::runtime_error("Connection nicht vorhanden bei "
			       "disconnectModules!");
    
    m_connections.erase(it);
  }


  void Graph::deleteModule(int moduleID)
  {
    for (GraphNodeList::iterator i = m_nodes.begin();
	 i != m_nodes.end(); ++i)
      {
	if ((*i)->moduleID() == moduleID) // found
	  {	      
	    // delete controllValues from all controllsets
	    for (unsigned int input=0;input<(*i)->spec().inputs().size();++input)
	      {
		// all snapshots
		for (Graph::ValueSetMap::iterator i=valueSets.begin();i!=valueSets.end();++i)
		  {
		    i->second->deleteControllValue(moduleID,input);
		  }
	      }
	    m_nodes.erase(i);		
	    break;
	  }
      }

		
  }


  void Graph::setModuleData(int moduleID,int type, const utils::Buffer& buf)
  {
    for (GraphNodeList::iterator i = m_nodes.begin();
	 i != m_nodes.end(); ++i)
      {
	if ((*i)->moduleID()==moduleID) // found
	  {
	    (*i)->setData(type,buf);
	    break;
	  }
      }
  }


  void Graph::unSetModuleData(int moduleID,int type)
  {
    for (GraphNodeList::iterator i = m_nodes.begin();
	 i != m_nodes.end(); ++i)
      {
	if ((*i)->moduleID() == moduleID) // found
	  {
	    (*i)->unSetData(type);
	    return;
	  }
      }
    throw std::runtime_error("module does not exist");
  }


  std::list<int> Graph::moduleDataList(int moduleID) const
  {
    for (GraphNodeList::const_iterator i = m_nodes.begin();
    	 i != m_nodes.end(); ++i)
      {
	if ((*i)->moduleID() == moduleID) // found
	  {
	    utils::AutoPtr<GraphNode> node = *i;
	    return node->moduleDataList();
	  }
      }

    throw std::runtime_error("module does not exist");
  }

  void Graph::setID(const std::string& id_)
  {
    m_id = id_;
  }

  std::string Graph::getID() const
  {
    return m_id;
  }

  void Graph::setName(const std::string& name_)
  {
    m_name=name_;
  }


  std::string Graph::getName() const
  {
    return m_name;
  }

  const Graph::ConnectionMap& Graph::connections() const
  {
    return m_connections;
  }

  const Graph::ValueSetMap& Graph::getValueSetMap() const
  {
    return valueSets;
  }

  const Graph::GraphNodeList& Graph::nodes() const
  {
    return m_nodes;
  }

  void Graph::clear()
  {
    // clear the graph    

    m_nodes.clear();
    m_connections.clear();
    valueSets.clear();


    
    // the ids start at 1, after removal of nodes the may be gaps
    m_maxModuleID = 0;
  }


  void Graph::newControlValueSet(const std::string& id,
				 const std::string& name)
  {
    ValueSetMap::const_iterator it = valueSets.find(id);
    if (it!=valueSets.end())
      throw std::runtime_error("snapshot with that name already exists "
			       "(Graph::newControlValueSet)");

    utils::AutoPtr<ControllValueSet> 
      newSet = utils::AutoPtr<ControllValueSet>(new ControllValueSet(id,name));

    valueSets[id]=newSet;
    // every module
    for (GraphNodeList::const_iterator node = m_nodes.begin();
	 node != m_nodes.end(); ++node)
      {	  
	const IModuleClassSpec& spec = (*node)->spec();
	// every input
	for (unsigned int input=0;input<spec.inputs().size();++input)
	  {					
	    newSet->setControlValue((*node)->moduleID(), input,
				 spec.defaultValue(input));
	  }
      }
  }

  void Graph::setControlValue(const std::string& id,
			      int nodeID,int intputIndex,
			      const utils::Buffer& value)
  {
    ValueSetMap::iterator it= valueSets.find(id);
    if (it == valueSets.end())
      throw std::runtime_error("No controlvalueset at "
			       "Graph::setControlValue()");

    it->second->setControlValue(nodeID,intputIndex,value);
  }

  void Graph::renameControllValueSet(const std::string& snapID,
				     const std::string& newSnapName)
  {
    ValueSetMap::iterator it = valueSets.find(snapID);

    if (it == valueSets.end())
      throw std::runtime_error("No such Snapshot at "
			       "Graph::renameControllValueSet()");

    /*    ValueSetMap::iterator it2 = valueSets.find(newSnapName);
    if (it2 != valueSets.end())
      throw std::runtime_error("Snapshot already exists at "
      "Graph::renameControllValueSet()");*/

    it->second->setName(newSnapName);

  }

  void Graph::copyControllValueSet(const std::string& snapID,
				   const std::string& newID,
				   const std::string& newName)
  {
    ValueSetMap::iterator it = valueSets.find(snapID);

    if (it == valueSets.end())
      throw std::runtime_error("No such Snapshot at "
			       "Graph::copyControllValueSet()");

    /*
    ValueSetMap::iterator it2 = valueSets.find(newSnapName);
    if (it2 != valueSets.end())
      throw std::runtime_error("Snapshot already exists at "
			       "Graph::copyControllValueSet()");
    */

    utils::AutoPtr<ControllValueSet> 
      copySet = utils::AutoPtr<ControllValueSet>(new ControllValueSet(newID,
								      newName));
    valueSets[newID] = copySet;
	
    for (ControllValueSet::const_iterator it3 = it->second->begin();
	 it3 != it->second->end(); ++it3)
      {
	copySet->setControlValue(it3->first.first, it3->first.second,
				it3->second);
      }
	
  }

  void Graph::deleteControllValueSet(const std::string& snapID)
  {
    ValueSetMap::iterator it = valueSets.find(snapID);

    if (it == valueSets.end())
      throw std::runtime_error("No such Snapshot at "
			       "Graph::deleteControllValueSet()");

    valueSets.erase(it);
  }

  int Graph::addModule(const IModuleClassSpec& spec)
  {
    // the ids start at 1, after removal of nodes there may be gaps
    ++m_maxModuleID;

    this->addModule(spec,m_maxModuleID);	

    return m_maxModuleID;
  }

} // end of namespace model
