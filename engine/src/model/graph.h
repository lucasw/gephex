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
      typedef std::map<const std::string, utils::AutoPtr<ControllValueSet> > ValueSetMap;
      typedef std::map<std::pair<int,int>,utils::AutoPtr<GraphConnection> > ConnectionMap;
      typedef std::list<utils::AutoPtr<GraphNode> > GraphNodeList;

      Graph(const std::string& graphID, const std::string& graphName);
      ~Graph();

      void setID(const std::string& id_);
      std::string getID() const;

      // GraphName
      void setName(const std::string& name_);
      std::string getName() const;

      // GraphStructure
      int addModule(const IModuleClassSpec&);
      void addModule(const IModuleClassSpec&,				   
		     int moduleID);

      void connectModules(int moduleID1,int outputIndex,
			  int moduleID2,int inputIndex);
      void disconnectModules(int moduleID,int inputIndex);
      void deleteModule(int moduleID);
      const ConnectionMap& connections() const;
      const GraphNodeList& nodes() const;
      /** Deletes all Modules and Connections. */
      void clear();

      // ModuleData
      void setModuleData(int moduleID,int type,const utils::Buffer& buf);
      void unSetModuleData(int moduleID,int type);
      /** returns a list of set moduleDatas **/
      std::list<int> moduleDataList(int moduleID) const;

      // ControllValues
      void newControlValueSet(const std::string& id, const std::string& name);

      void setControlValue(const std::string& snapShotID,int nodeID,
			   int intputIndex, const utils::Buffer& newValue);

      void copyControllValueSet(const std::string& snapID,
				const std::string& newID,
				const std::string& newSnapName);

      void renameControllValueSet(const std::string& snapID,
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
