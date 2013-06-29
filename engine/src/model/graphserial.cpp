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
#include <sstream>

#include "graph.h"
#include "graphnode.h"
#include "graphconnection.h"
#include "controlvalueset.h"

#include "graphparser.h"

#include "interfaces/imoduleclassspec.h"
#include "utils/ilogger.h"

namespace model
{
  //-------------------------------------------------------------------------
  
  static const char ESCAPE_CHAR = '~';

  static bool must_escape(unsigned char c)
  {
    return c < 32 || c >= 126 || c == ESCAPE_CHAR || c == '<' || c == '>';
  }
  
  static std::string escape(unsigned char c)
  {
    static const char* char2hex = "0123456789abcdef";
    char e[4];
    e[0] = ESCAPE_CHAR;
    e[1] = char2hex[(c >> 4) & 15];
    e[2] = char2hex[c & 15];
    e[3] = 0;
    //    std::cout << "Escaping '" << c << "' -> '" << e <<"'\n";
    
    return std::string(e, 3);
  }

  inline char hex2int (char hex)
  {
    if (hex >= '0' && hex <= '9')
      return hex - '0';
    else if (hex >= 'a' && hex <= 'f')
      return hex - 'a' + 0xa;
    else
      throw std::runtime_error("no hexcode (utils::hex2int()");
  }

  static std::string::const_iterator 
  unescape(std::vector<unsigned char>& v,
           std::string::const_iterator begin,
           std::string::const_iterator end)
  {
    std::string::const_iterator it = begin;
    assert(*it == ESCAPE_CHAR);
    ++it;
    if (it == end)
      throw std::runtime_error("string ends in escape sequence");

    char hn = *it;
    ++it;
    if (it == end)
      throw std::runtime_error("string ends in escape sequence");

    char ln = *it;

    v.push_back(hex2int(ln) + (hex2int(hn) << 4));
    return it;
  }

  /**
   * Converts a string to a buffer.
   * The string has '~' as a escape code and encodes all
   * characters outside [32,126] and some special chars
   * with this escape code followed
   * by the hex representation of the value.
   * For example, the char value 1 is encoded as "~01".
   */
  static utils::Buffer string_to_buffer(const std::string& s)
  {
    std::vector<unsigned char> v;

    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
      {
        char c = *it;
        if (c == ESCAPE_CHAR)
          {
            it = unescape(v, it, s.end());
          }
        else
          v.push_back(static_cast<unsigned char>(c));
      }

    return utils::Buffer(&v[0], v.size());
  }

  /**
   * Converts a buffer to a string.
   * The string has '~' as a escape code and encodes all
   * characters outside [32,126] + some special chars
   * with this escape code followed
   * by the hex representation of the value.
   * For example, the char value 1 is encoded as "~01".
   */
  static std::string buffer_to_string(const utils::Buffer& b)
  {
    std::string result;
    const unsigned char* ptr = b.getPtr();
    int len = b.getLen();
    for (int i = 0; i < len; ++i)
      {
        unsigned char uc = ptr[i];
        if (must_escape(uc))
          result += escape(uc);
        else
          result += static_cast<char>(uc);
      }

    return result;
  }

  //-------------------------------------------------------------------------

  static std::string int_to_string(int i)
  {
    std::ostringstream os;
    os << i;
    return os.str();
  }

  static int string_to_int(const std::string& s)
  {
    std::istringstream is(s);
    
    int res;
    is >> res;
    
    if (!is)
      throw std::runtime_error("invalid string: could not convert to int");

    return res;
  }

  static gparser::SConnection connection_to_syntax(const GraphConnection& c,
                                                   const Graph& g)
  {
    std::string node1_id =  int_to_string(c.id1());
    int plug1_index = c.outIndex();
    std::string plug1_id = g.getOutputID(c.id1(), plug1_index);
    
    std::string node2_id = int_to_string(c.id2());
    int plug2_index = c.inIndex();
    std::string plug2_id = g.getInputID(c.id2(), plug2_index);

    return gparser::SConnection(gparser::SPlug(node1_id, plug1_id),
                                gparser::SPlug(node2_id, plug2_id));

  }

  static gparser::SNode node_to_syntax(const GraphNode& n)
  {
    int moduleIndex = n.moduleID();
    std::string moduleID = int_to_string(moduleIndex);
    std::string type = n.spec().moduleClassName();

    std::list<gparser::SDataItem> dataitems;

    const std::map<int,utils::Buffer>& data = n.data();
    for (std::map<int,utils::Buffer>::const_iterator dataItem=data.begin();
         dataItem != data.end(); ++dataItem)
      {
        //        std::cout << "Converting data...\n";
        std::string key = int_to_string(dataItem->first);
        //        std::cout << "key = " << key << "\n";
        std::string val = buffer_to_string(dataItem->second);
        //        std::cout << "val = " << val << "\n";

        dataitems.push_back(gparser::SDataItem(key, val));
      }

    return gparser::SNode(moduleID, type, dataitems);
  }

  static gparser::SGraph graph_to_syntax(const Graph& g)
  {
    std::string graph_id = g.getID();
    std::string graph_name = g.getName();
    
    std::list<gparser::SDataItem> gditems;
    const std::map<int, utils::Buffer>& gdata = g.data();
    for (std::map<int, utils::Buffer>::const_iterator it = gdata.begin();
         it != gdata.end(); ++it)
      {
        std::string key = int_to_string(it->first);
        //        std::cout << "key = " << key << "\n";
        std::string val = buffer_to_string(it->second);
        //        std::cout << "val = " << val << "\n";

        gditems.push_back(gparser::SDataItem(key, val));
      }

    std::list<gparser::SNode> ns;
    const Graph::GraphNodeList& nodes = g.nodes();
    for ( Graph::GraphNodeList::const_iterator node = nodes.begin();
	  node != nodes.end(); ++node)
      {
	ns.push_back( node_to_syntax(**node) );
      }

    std::list<gparser::SConnection> cs;
    const Graph::ConnectionMap& connections = g.connections();
    for(Graph::ConnectionMap::const_iterator i = connections.begin();
	i != connections.end(); ++i)
      {
        cs.push_back( connection_to_syntax(*i->second, g) );
      }

    std::list<gparser::SSnapshot> snaps;
    const Graph::ValueSetMap& valueSets = g.getValueSetMap();
    for (Graph::ValueSetMap::const_iterator it = valueSets.begin();
         it != valueSets.end(); ++it)
      {
        std::string snap_id = it->first;
        std::string snap_name = it->second->getName();

        std::list<gparser::SValue> values;
        for (ControlValueSet::const_iterator valpair = it->second->begin();
             valpair != it->second->end(); ++valpair)
          {
            int moduleIndex = valpair->first.first;
            int plugIndex = valpair->first.second;

            std::string moduleID = int_to_string(moduleIndex);

            std::string plugID = g.getInputID(moduleIndex, plugIndex);

            utils::Buffer val = valpair->second;
            std::string value = buffer_to_string(val);
	    
            values.push_back(gparser::SValue(gparser::SPlug(moduleID,
                                                            plugID),
                                             value));
          }

        //        std::cout << "snap: " << snap_id << "\n";
        snaps.push_back(gparser::SSnapshot(snap_id, snap_name, values));
      }
    
    return gparser::SGraph(graph_id, graph_name, gditems, ns, cs, snaps);
  }

  std::ostream& operator<< (std::ostream& s, const model::Graph& graph)
  {
    gparser::serialize(s, graph_to_syntax(graph));
    return s;
  }

  //-------------------------------------------------------------------------

  static void graph_from_syntax(const gparser::SGraph& sg,
                                model::Graph& graph,
                                const SpecMap& specMap,
                                utils::ILogger& logger,
                                bool nodummy)
  {
    graph.clear();
    typedef std::map<int, utils::AutoPtr<IModuleClassSpec> > IDMap;
    IDMap moduleSpecs;

    std::map<int, bool> module_valid;

    // parse and build
    graph.setID(sg.id());
    graph.setName(sg.name());

    for (std::list<gparser::SDataItem>::const_iterator 
           di_it = sg.dataitems().begin();
         di_it != sg.dataitems().end();
         ++di_it)
          {
            const gparser::SDataItem& di = *di_it;
	    int key = string_to_int(di.key());
	    utils::Buffer value = string_to_buffer(di.value());
	    if (nodummy)
              {
                graph.setData(key, value);
              }
	  } // dataitems

    for (std::list<gparser::SNode>::const_iterator nit = sg.nodes().begin();
         nit != sg.nodes().end(); ++nit)
      {
        const gparser::SNode& node = *nit;
	int moduleID = string_to_int(node.id());
        module_valid[moduleID] = false;

	std::string moduleClassName = node.type();
	if (nodummy) 
	  {
	    SpecMap::const_iterator 
	      it = specMap.find(moduleClassName);
	    if (it == specMap.end())
	      {
                std::ostringstream os;
		os << "No such module class: '" 
                   << moduleClassName << "' - ignoring module";               
		logger.warning("Model::GraphSerial",  os.str());
	      }
	    else
              {
                graph.addModule(*it->second,moduleID) ;
                moduleSpecs.insert(std::make_pair(moduleID, it->second));
                module_valid[moduleID] = true;
              }
	  }

        for (std::list<gparser::SDataItem>::const_iterator 
               di_it = node.dataitems().begin();
             di_it != node.dataitems().end();
             ++di_it)
          {
            const gparser::SDataItem& di = *di_it;
	    int key = string_to_int(di.key());
	    utils::Buffer value =  string_to_buffer(di.value());
	    if (nodummy && module_valid[moduleID])
              {
                graph.setModuleData(moduleID, key, value);
              }
	  } // dataitems
      } // nodes


    const std::list<gparser::SConnection>& cs = sg.connections();
    for (std::list<gparser::SConnection>::const_iterator co_it = cs.begin();
         co_it != cs.end(); ++co_it)
      {
        gparser::SConnection c = *co_it;
	int moduleID1 = string_to_int(c.from().node_id());

	std::string outplug = c.from().plug_id();

	int moduleID2 = string_to_int(c.to().node_id());

	std::string inplug = c.to().plug_id();
	if (nodummy)
          {
            IDMap::const_iterator it1 = moduleSpecs.find(moduleID1);
            IDMap::const_iterator it2 = moduleSpecs.find(moduleID2);
            if (it1 == moduleSpecs.end() || it2 == moduleSpecs.end())
              {
                std::ostringstream os;
                os << "Invalid ids at connect: " 
                   << "from: '" << moduleID1 << "' to: '" << moduleID2
                   << "' - ignoring connection";
                logger.warning("Model::GraphSerial", os.str());
              }
            else
              {
                utils::AutoPtr<IModuleClassSpec> spec1 = it1->second;
                utils::AutoPtr<IModuleClassSpec> spec2 = it2->second;

                try
                  {
                    int outputIndex = spec1->indexFromOutputID(outplug);
                    int inputIndex = spec2->indexFromInputID(inplug);
                    graph.connectModules(moduleID1,
                                         outputIndex,
                                         moduleID2,
                                         inputIndex);
                  }
                catch (std::exception& e)
                  {
                    std::ostringstream os;
                    os << "Invalid plug id at connect: " 
                       << "outplug: '" << outplug << "' inplug: '" << inplug
                       << "' - ignoring connection";
                    logger.warning("Model::GraphSerial", os.str());
                  }
              }
          }
      }// connections

    const std::list<gparser::SSnapshot>& snaps = sg.snapshots();
    for (std::list<gparser::SSnapshot>::const_iterator sn_it = snaps.begin();
         sn_it != snaps.end(); ++sn_it)
      {
        const gparser::SSnapshot& snap = *sn_it;

	graph.newControlValueSet(snap.id(), snap.name());

        const std::list<gparser::SValue>& values = snap.values();
	for (std::list<gparser::SValue>::const_iterator v_it = values.begin();
             v_it != values.end(); ++v_it)
	  {
            const gparser::SValue& v = *v_it;
	    int moduleID = string_to_int(v.plug().node_id());

	    std::string plugID = v.plug().plug_id();
	    utils::Buffer value = string_to_buffer(v.value());

	    if (nodummy && module_valid[moduleID])
              {
                IDMap::const_iterator it = moduleSpecs.find(moduleID);
                if (it == moduleSpecs.end())
                  throw std::runtime_error("Invalid moduleID at snapshot");

                utils::AutoPtr<IModuleClassSpec> spec = it->second;

                try
                  {
                    graph.setControlValue(snap.id(), moduleID, 
                                          spec->indexFromInputID(plugID),
                                          value);
                  }
                catch (std::exception& e)
                  {
                    std::ostringstream os;
                    os << "Invalid plug id in snapshot: " 
                       << "moduleID: '" << moduleID << "' plug: '" << plugID
                       << "' - ignoring value";
                    logger.warning("Model::GraphSerial", os.str());
                  }
              }
          } //values
      } //snapshots
  }  

  std::istream& deserializeGraph(std::istream& s,
                                 Graph& graph,
                                 const SpecMap& specMap,
                                 utils::ILogger& logger,
                                 bool nodummy)
  {
    std::ostringstream os;
    
    int i;
    while((i = s.get()) && i != EOF)
      {
	char c = static_cast<char>(i);
        os.put(c);
      }

    std::string graph_text = os.str();

    gparser::SGraph sg = gparser::parse(graph_text);

    graph_from_syntax(sg, graph, specMap, logger, nodummy);
    
    return s;
  }
}
