/* This source file is a part of the GePhex Project.

Copyright (C) 2001-2003 

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
    s << "<data>\n";
    const std::map<int,utils::Buffer>& data = node.data();
    for (std::map<int,utils::Buffer>::const_iterator dataItem=data.begin();dataItem!=data.end();++dataItem)
      {
	s << "<dataitem>";
	s << "<key>" << (*dataItem).first << "</key>";
	s << (*dataItem).second;
	s << "</dataitem>\n";
      }
    s << "</data>\n";	
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
    s << "<name>" << graph.getName() << "</name>\n";
    s << "<nodes>\n";
    
    const Graph::GraphNodeList& nodes = graph.nodes();
    for ( Graph::GraphNodeList::const_iterator node = nodes.begin();
	  node != nodes.end(); ++node)
      {
	s << **node << "\n";
      }		
    s << "</nodes>\n";
    s << "<connections>\n";
    const Graph::ConnectionMap& connections = graph.connections();
    for(Graph::ConnectionMap::const_iterator i = connections.begin();
	i != connections.end(); ++i)
      {
	s << *i->second << "\n"; // serialize the connection
      }
    s << "</connections>\n";
    // snapshots start
    s << "<snapshots>\n";
    const Graph::ValueSetMap valueSets=graph.getValueSetMap();
    for (Graph::ValueSetMap::const_iterator it=valueSets.begin();it!=valueSets.end();++it)
      {
	s << "<snapshot>\n";
        s << "<id>" << it->first << "</id>";
        s << "<name>" << it->second->getName() << "</name>";
        s << "<values>\n";
        for (ControllValueSet::const_iterator
	       valpair = it->second->begin();valpair!=it->second->end();++valpair)
          {
	    s << "<value>";
            s << "<moduleid>" << valpair->first.first << "</moduleid>";
            s << "<nodeid>" << valpair->first.second << "</nodeid>";
            s << valpair->second;
	    s << "</value>\n";
          }
        s << "</values>\n";
	s << "</snapshot>\n";
      }
    s << "</snapshots>\n";
    // snapshots stop
    s << "</graph>";
    return s;
  }
  
  std::istream& deserializeGraph (std::istream& s, model::Graph& graph,
				  const std::map<std::string,
				  utils::AutoPtr<IModuleClassSpec> >& specMap,
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
		const std::string errorText("No such module class: '" + moduleClassName +"'");
		throw std::runtime_error(errorText);
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
