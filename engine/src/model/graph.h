#ifndef _INCLUDED_GRAPH_H_
#define _INCLUDED_GRAPH_H_

#include <map>
#include <vector>
#include <list>
#include <string>
#include <iosfwd>

#include "utils/autoptr.h"
//#include "controllvalueset.h"


namespace utils {
  class Buffer;
}

class IModuleClassSpec;

namespace model
{
  class GraphNode;
  class GraphConnection;
  class ControllValueSet;

  class Graph
    {
    public:
      typedef const std::string ControlValueSetID; 
      typedef int ModuleID;
      typedef utils::AutoPtr< ControllValueSet > ControlValueSetPtr; 
      typedef std::map< ControlValueSetID, ControlValueSetPtr > ValueSetMap;
      typedef utils::AutoPtr< GraphConnection > ConnectionPtr;
      typedef utils::AutoPtr< GraphNode > NodePtr;
      typedef std::list< NodePtr > GraphNodeList;

      typedef std::map<std::pair<int,int>, ConnectionPtr > ConnectionMap;

      /**
       * Creates a new Graph
       * \param graphID unique ID for the graph
       * \param graphName userreadable name for the graph
       */
      Graph(const std::string& graphID, const std::string& graphName);

      /**
       * destroys the Graphobject
       */
      ~Graph();

      /**
       * change the ID of the graph
       * \todo the id should not change. remove this
       */
      void setID(const std::string& id_);

      /**
       * retrieve the unique id of the graph
       */
      std::string getID() const;

      /**
       * changes the name of the Graph
       * \param new name
       */
      void setName(const std::string& name_);

      /**
       * get the name of the graph
       * \returns the name of the graph
       */
      std::string getName() const;

      /**
       * add a new module to the graph
       * \param spec of the new module
       * \returns the ID of the module
       */
      ModuleID addModule(const IModuleClassSpec&);
      void addModule(const IModuleClassSpec&,				   
		     ModuleID moduleID);

      void connectModules(ModuleID moduleID1, int outputIndex,
			  ModuleID moduleID2, int inputIndex);
      void disconnectModules(ModuleID moduleID,int inputIndex);
      void deleteModule(ModuleID moduleID);
      const ConnectionMap& connections() const;
      const GraphNodeList& nodes() const;
      /** Deletes all Modules and Connections. */
      void clear();

      // ModuleData
      void setModuleData(ModuleID moduleID,int type,const utils::Buffer& buf);
      void unSetModuleData(ModuleID moduleID,int type);
      /** returns a list of set moduleDatas **/
      std::list<int> moduleDataList(ModuleID moduleID) const;

      // ControllValues
      void newControlValueSet(ControlValueSetID&, const std::string& name);

      void setControlValue(ControlValueSetID& snapShotID, 
			   ModuleID nodeID,
			   int inputIndex, 
			   const utils::Buffer& newValue);

      void copyControllValueSet(ControlValueSetID& snapID,
				ControlValueSetID& newID,
				const std::string& newSnapName);

      void renameControllValueSet(ControlValueSetID& snapID,
				  const std::string& newSnapName);

      void deleteControllValueSet(const std::string& snapID);
      const ValueSetMap& getValueSetMap() const;

    private:
      Graph(const Graph&); //not impl.
      Graph& operator=(const Graph&); //not impl.

      std::string m_id;
      std::string m_name;
      int m_maxModuleID;    

      // graph structure	
      GraphNodeList m_nodes;
      ConnectionMap m_connections;

      // controll Value Sets
      ValueSetMap valueSets;
    };  

}



#endif
