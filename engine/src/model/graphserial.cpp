#include "graphserial.h"

#include <iostream>

#include "interfaces/imoduleclassspec.h"

#include "graph.h"
#include "graphnode.h"
#include "graphconnection.h"
#include "controllvalueset.h"

#include "utils/xmlutils.h"
#include "utils/bufferutils.h"

namespace model
{

  std::ostream& operator<< (std::ostream& s, const GraphNode& node)
  {
	s << "<node>";
	s << "<id>" << node.moduleID() << "</id>";
	s << "<type>" << node.spec().moduleClassName() << "</type>";
	s << "<data>";
	const std::map<int,utils::Buffer>& data = node.data();
	for (std::map<int,utils::Buffer>::const_iterator dataItem=data.begin();dataItem!=data.end();++dataItem)
	  {
	    s << "<dataitem>";
	    s << "<key>" << (*dataItem).first << "</key>";
	    s << (*dataItem).second;
	    s << "</dataitem>";
	  }
	s << "</data>";			
	s << "</node>";

	return s;
  }

  std::ostream& operator<<(std::ostream& s, const GraphConnection& connect)
{
	s << "<connect>";
	s << "<from>";
	s << "<id>" << connect.id1() << "</id>";
	s << "<plug>" << connect.outIndex() << "</plug>";
	s << "</from>";
	s << "<to>";
	s << "<id>" << connect.id2() << "</id>";
	s << "<plug>" << connect.inIndex() << "</plug>";
	s << "</to>";
	s << "</connect>";
	return s;
}


  std::ostream& operator<< (std::ostream& s, const model::Graph& graph)
  {
    s << "<graph>";
    s << "<id>" << graph.getID() << "</id>";
    s << "<name>" << graph.getName() << "</name>";
    s << "<nodes>";

    const Graph::GraphNodeList& nodes = graph.nodes();
    for ( Graph::GraphNodeList::const_iterator node = nodes.begin();
		 node != nodes.end(); ++node)
      {
	s << **node;
      }		
    s << "</nodes>";
    s << "<connections>";
    const Graph::ConnectionMap& connections = graph.connections();
    for(Graph::ConnectionMap::const_iterator i = connections.begin();
	i != connections.end(); ++i)
      {
	s << *i->second; // serialize the connection
      }
    s << "</connections>";
    // snapshots start
    s << "<snapshots>";
    const Graph::ValueSetMap valueSets=graph.getValueSetMap();
    for (Graph::ValueSetMap::const_iterator it=valueSets.begin();it!=valueSets.end();++it)
    {
      s << "<snapshot>";
        s << "<id>" << it->first << "</id>";
        s << "<name>" << it->second->getName() << "</name>";
        s << "<values>";
        for (ControllValueSet::const_iterator
          valpair = it->second->begin();valpair!=it->second->end();++valpair)
          {
          s << "<value>";
            s << "<moduleid>" << valpair->first.first << "</moduleid>";
            s << "<nodeid>" << valpair->first.second << "</nodeid>";
            s << valpair->second;
          s << "</value>";
          }
        s << "</values>";
      s << "</snapshot>";
    }
    s << "</snapshots>";
    // snapshots stop
    s << "</graph>";
    return s;
  }

  /*std::istream& operator>> (std::istream& s, model::Graph& graph)
	{
		return deserializeGraph(s, graph,true);
	}*/

  std::istream& deserializeGraph (std::istream& s, model::Graph& graph,
	  const std::map<std::string,utils::AutoPtr<IModuleClassSpec> >& specMap,
	  bool nodummy)
  {
    using utils::checktag;
    using utils::checktagloop;
    using utils::extractbetweenTags;

    graph.clear();

    // parse and build
    checktag(s,"<graph>");
      checktag(s,"<id>");
        std::string id;
        extractbetweenTags(s,id);
        graph.setID(id);
      checktag(s,"</id>");
      checktag(s,"<name>");
        std::string name;
        extractbetweenTags(s,name);
        graph.setName(name);
      checktag(s,"</name>");
      checktag(s,"<nodes>");
        while (checktagloop(s,"<node>","</nodes>"))
        {
	        checktag(s,"<id>");
	          int moduleID;
  	        s >> moduleID;
	        checktag(s,"</id>");
	        checktag(s,"<type>");
	          std::string moduleClassName;
	          extractbetweenTags(s,moduleClassName);
	        checktag(s,"</type>");
	        if (nodummy) 
			{
				std::map<std::string,utils::AutoPtr<IModuleClassSpec> >::const_iterator 
					it = specMap.find(moduleClassName);
				if (it == specMap.end())
				{
					//TODO
				}
				else
					graph.addModule(*it->second,moduleID) ;
			}
	        checktag(s,"<data>");
	          while (checktagloop(s,"<dataitem>","</data>"))
	          {						
	            checktag(s,"<key>");
	              int key;
	              s >> key;
	            checktag(s,"</key>");
	            utils::Buffer value;
	            s >> value;
	            if (nodummy) graph.setModuleData(moduleID,key,value);
	          checktag(s,"</dataitem>");
	        } // </data>
	      checktag(s,"</node>");
      } // </nodes>
      checktag(s,"<connections>");
        while (checktagloop(s,"<connect>","</connections>"))
        {
	        checktag(s,"<from>");
	          checktag(s,"<id>");
	            int moduleID1;
	            s >> moduleID1;
	          checktag(s,"</id>");
	          checktag(s,"<plug>");
	            int outplug;
	            s >> outplug;	
	          checktag(s,"</plug>");
	        checktag(s,"</from>");
	        checktag(s,"<to>");
	          checktag(s,"<id>");
	            int moduleID2;
	            s >> moduleID2;
	          checktag(s,"</id>");
	          checktag(s,"<plug>");
	            int inplug;
	            s >> inplug;	
	          checktag(s,"</plug>");
	        checktag(s,"</to>");
    	  checktag(s,"</connect>");
	      if (nodummy) graph.connectModules(moduleID1, outplug, moduleID2, inplug);
      } // "</connections>"
      checktag(s,"<snapshots>");
        while (checktagloop(s,"<snapshot>","</snapshots>"))
        {
          checktag(s,"<id>");
	   std::string snapShotID;
	   extractbetweenTags(s,snapShotID);
          checktag(s,"</id>");
          checktag(s,"<name>");
            std::string snapShotName;
     	      extractbetweenTags(s,snapShotName);
          checktag(s,"</name>");
           graph.newControlValueSet(snapShotID,snapShotName);
          checktag(s,"<values>");
            while (checktagloop(s,"<value>","</values>"))
            {
              checktag(s,"<moduleid>");
                int moduleID;
                s >> moduleID;
              checktag(s,"</moduleid>");
              checktag(s,"<nodeid>");
                int nodeID;
                s >> nodeID;
              checktag(s,"</nodeid>");
	            utils::Buffer value;
	            s >> value;
              if (nodummy) graph.setControlValue(snapShotID,moduleID,nodeID,value);
            checktag(s,"</value>");
          } // </values>
        checktag(s,"</snapshot>");
      } // </snapshots>
    checktag(s,"</graph>");
    return s;
  }

}
