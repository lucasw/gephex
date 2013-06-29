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

#include "graphparser.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "utils/xmlutils.h"

namespace model
{
  namespace gparser  
  {
    //-------------------------------------------------------------------
    
    SPlug::SPlug(const std::string& node_id,
		 const std::string& plug_id)
      : m_node_id(node_id), m_plug_id(plug_id)
    {
    }

    std::string SPlug::node_id() const
    {
      return m_node_id;
    }

    std::string SPlug::plug_id() const
    {
      return m_plug_id;
    }

    //-------------------------------------------------------------------

    SValue::SValue(const SPlug& plug, std::string& value)
      : m_plug(plug), m_value(value)
    {
    }

    const SPlug& SValue::plug() const
    {
      return m_plug;
    }

    const std::string& SValue::value() const
    {
      return m_value;
    }

    //-------------------------------------------------------------------

    SSnapshot::SSnapshot(const std::string& id,
			 const std::string& name,
			 std::list<SValue>& values)
      : m_id(id), m_name(name), m_values(values)
    {
    }

    std::string SSnapshot::id() const
    {
      return m_id;
    }

    std::string SSnapshot::name() const
    {
      return m_name;
    }

    const std::list<SValue>& SSnapshot::values() const
    {
      return m_values;
    }

    //-------------------------------------------------------------------

    SConnection::SConnection(const SPlug& from, const SPlug& to)
      : m_from(from), m_to(to)
    {
    }

    const SPlug& SConnection::from() const
    {
      return m_from;
    }

    const SPlug& SConnection::to() const
    {
      return m_to;
    }

    //-------------------------------------------------------------------

    SDataItem::SDataItem(const std::string& key,
			 std::string& value)
      : m_key(key), m_value(value)
    {
    }

    std::string SDataItem::key() const
    {
      return m_key;
    }
    const std::string& SDataItem::value() const
    {
      return m_value;
    }

    //-------------------------------------------------------------------

    SNode::SNode(const std::string& id,
		 const std::string& type,
		 std::list<SDataItem>& dataitems)
      : m_id(id), m_type(type), m_dataitems(dataitems)
    {
    }

    std::string SNode::id() const
    {
      return m_id;
    }

    std::string SNode::type() const
    {
      return m_type;
    }

    const std::list<SDataItem>& SNode::dataitems() const
    {
      return m_dataitems;
    }

    //-------------------------------------------------------------------

    SGraph::SGraph(const std::string& id,
		   const std::string& name,
                   std::list<SDataItem>& dataitems,
		   std::list<SNode>& nodes,
		   std::list<SConnection>& connections,
		   std::list<SSnapshot>& snapshots)
      : m_id(id), m_name(name), 
        m_dataitems(dataitems), m_nodes(nodes),
	m_connections(connections), m_snapshots(snapshots)
    {
    }

    std::string SGraph::id() const
    {
      return m_id;
    }

    std::string SGraph::name() const
    {
      return m_name;
    }

    const std::list<SDataItem>& SGraph::dataitems() const
    {
      return m_dataitems;
    }

    const std::list<SNode>& SGraph::nodes() const
    {
      return m_nodes;
    }

    const std::list<SConnection>& SGraph::connections() const
    {
      return m_connections;
    }

    const std::list<SSnapshot>& SGraph::snapshots() const
    {
      return m_snapshots;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_dataitem(utils::xml::Iterator begin,
					utils::xml::Iterator end,
					SDataItem& dataitem)
    {
      utils::xml::Iterator i = begin;
      std::string key;
      std::string value;
      
      i = utils::xml::tagOpens(i, end, "dataitem");

      i = utils::xml::leafTag(i, end, "key", key);
      i = utils::xml::leafTag(i, end, "buf", value);

      i = utils::xml::tagCloses(i, end, "dataitem");
      
      dataitem = SDataItem(key, value);

      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_data(utils::xml::Iterator begin,
				    utils::xml::Iterator end,
				    std::list<SDataItem>& data)
    {
      utils::xml::Iterator i = begin;

      i = utils::xml::tagOpens(i, end, "data");

      while (utils::xml::next_tag_name(i, end) == "dataitem")
        {	
          SDataItem dataitem;
          i = parse_dataitem(i, end, dataitem);
          data.push_back(dataitem);
        }
          
      i = utils::xml::tagCloses(i, end, "data");

      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_node(utils::xml::Iterator begin,
				    utils::xml::Iterator end,
				    SNode& node)
    {
      //      std::cout << "parse node\n";
      utils::xml::Iterator i = begin;
      std::string id;
      std::string type;
      std::list<SDataItem> data;
      
      i = utils::xml::tagOpens(i, end, "node");
      i = utils::xml::leafTag(i, end, "id", id);
      i = utils::xml::leafTag(i, end, "type", type);
      i = parse_data(i, end, data);
      i = utils::xml::tagCloses(i, end, "node");

      node = SNode(id, type, data);

      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_nodes(utils::xml::Iterator begin,
				     utils::xml::Iterator end,
				     std::list<SNode>& nodes)
    {
      //      std::cout << "parse nodes\n";
      utils::xml::Iterator i = begin;

      i = utils::xml::tagOpens(i, end, "nodes");
      
      while (utils::xml::next_tag_name(i, end) == "node")
      {	
	SNode node;
	i = parse_node(i, end, node);
	nodes.push_back(node);
      }

      i = utils::xml::tagCloses(i, end, "nodes");
      
      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_plug(utils::xml::Iterator begin,
				    utils::xml::Iterator end,
				    const std::string& tag_name,
				    SPlug& plug)
    {
      utils::xml::Iterator i = begin;

      std::string node_id;
      std::string plug_id;

      i = utils::xml::tagOpens(i, end, tag_name);
      
      i = utils::xml::leafTag(i, end, "node_id", node_id);
      i = utils::xml::leafTag(i, end, "plug_id", plug_id);

      i = utils::xml::tagCloses(i, end, tag_name);

      plug = SPlug(node_id, plug_id);
      
      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_connection(utils::xml::Iterator begin,
					  utils::xml::Iterator end,
					  SConnection& connection)
    {
      //      std::cout << "parse connection\n";
      utils::xml::Iterator i = begin;
      SPlug from;
      SPlug to;
      
      i = utils::xml::tagOpens(i, end, "connect");
      i = parse_plug(i, end, "from", from);
      i = parse_plug(i, end, "to", to);
      i = utils::xml::tagCloses(i, end, "connect");

      connection = SConnection(from, to);

      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_connections(utils::xml::Iterator begin,
					   utils::xml::Iterator end,
					   std::list<SConnection>& connections)
    {
      //      std::cout << "parse connections\n";
      utils::xml::Iterator i = begin;

      i = utils::xml::tagOpens(i, end, "connections");
      
      while (utils::xml::next_tag_name(i, end) == "connect")
      {	
	SConnection connection;
	i = parse_connection(i, end, connection);
	connections.push_back(connection);
      }

      i = utils::xml::tagCloses(i, end, "connections");
      
      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_value(utils::xml::Iterator begin,
				     utils::xml::Iterator end,
				     SValue& value)
    {
      utils::xml::Iterator i = begin;
      SPlug plug;
      std::string buf;
      
      i = utils::xml::tagOpens(i, end, "value");
      i = parse_plug(i, end, "plug", plug);
      i = utils::xml::leafTag(i, end, "buf", buf);
      i = utils::xml::tagCloses(i, end, "value");

      value = SValue(plug, buf);

      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_values(utils::xml::Iterator begin,
				      utils::xml::Iterator end,
				      std::list<SValue>& values)
    {
      utils::xml::Iterator i = begin;

      i = utils::xml::tagOpens(i, end, "values");
      
      while (utils::xml::next_tag_name(i, end) == "value")
      {	
	SValue value;
	i = parse_value(i, end, value);
	values.push_back(value);
      }

      i = utils::xml::tagCloses(i, end, "values");
      
      return i;
    }

    //-------------------------------------------------------------------

    utils::xml::Iterator parse_snapshot(utils::xml::Iterator begin,
					utils::xml::Iterator end,
					SSnapshot& snapshot)
    {
      utils::xml::Iterator i = begin;
      std::string id;
      std::string name;
      std::list<SValue> values;
      
      i = utils::xml::tagOpens(i, end, "snapshot");
      i = utils::xml::leafTag(i, end, "id", id);
      i = utils::xml::leafTag(i, end, "name", name);
      i = parse_values(i, end, values);
      i = utils::xml::tagCloses(i, end, "snapshot");

      snapshot = SSnapshot(id, name, values);

      return i;
    }

    utils::xml::Iterator parse_snapshots(utils::xml::Iterator begin,
					 utils::xml::Iterator end,
					 std::list<SSnapshot>& snapshots)
    {
      //      std::cout << "parse snapshots\n";
      utils::xml::Iterator i = begin;

      i = utils::xml::tagOpens(i, end, "snapshots");
      
      while (utils::xml::next_tag_name(i, end) == "snapshot")
      {	
	SSnapshot snapshot;
	i = parse_snapshot(i, end, snapshot);
	snapshots.push_back(snapshot);
      }

      i = utils::xml::tagCloses(i, end, "snapshots");
      
      return i;
    }

    //-------------------------------------------------------------------

    const SGraph parse(const std::string& text)
    {

      utils::xml::Iterator i = text.begin();
      utils::xml::Iterator end = text.end();

      std::string graph_id;
      std::string graph_name;
      std::list<SNode> nodes;
      std::list<SConnection> connections;
      std::list<SSnapshot> snapshots;

      try
	{
	  i = utils::xml::tagOpens(i, end, "graph");
	  i = utils::xml::leafTag(i, end, "id", graph_id);
	  i = utils::xml::leafTag(i, end, "name", graph_name);

          std::list<SDataItem> data;
          std::string tagname = utils::xml::next_tag_name(i, end);

          // older graphs don't have the data section      
          if (tagname == "data")
            {
              i = parse_data(i, end, data);
            }

	  i = parse_nodes(i, end, nodes);

	  i = parse_connections(i, end, connections);
	  i = parse_snapshots(i, end, snapshots);
	  i = utils::xml::tagCloses(i, end, "graph");

	  return SGraph(graph_id,
			graph_name,
                        data,
			nodes,
			connections,
			snapshots);
	}
      catch(std::exception& e)
	{
	  std::string msg = "Error while parsing Graph: ";
	  msg += e.what();
	  throw std::runtime_error(msg.c_str());
	}
    }

    //-------------------------------------------------------------------

    static void serialize_plug(std::ostream& s, const SPlug& plug,
                               const std::string& tag)
    {
      s << "<" << tag << "> <node_id>" << plug.node_id() << "</node_id> "
        << "<plug_id>" << plug.plug_id() << "</plug_id> </" << tag << ">\n";
    }

    //-------------------------------------------------------------------

    class ValueSerializer
    {
    public:
      ValueSerializer(std::ostream& s) : m_stream(s) {}
      
      void operator()(const SValue& v)
      {
        m_stream << "<value>";
        serialize_plug(m_stream, v.plug(), "plug");
        m_stream << "<buf>" << v.value() << "</buf>"
                 << "</value>\n";
      }

    private:
      std::ostream& m_stream;
    };

    class SnapshotSerializer
    {
    public:
      SnapshotSerializer(std::ostream& s) : m_stream(s) {}
      
      void operator()(const SSnapshot& s)
      {
        m_stream << "<snapshot> <id>" << s.id() << "</id> <name>"
                 << s.name() << "</name>\n";
        m_stream << "<values>\n";

        ValueSerializer vs(m_stream);
        std::for_each(s.values().begin(),
                      s.values().end(),
                      vs);

        m_stream << "</values>\n";
        m_stream << "</snapshot>\n";
      }

    private:
      std::ostream& m_stream;
    };

    //-------------------------------------------------------------------

    class ConnectionSerializer
    {
    public:
      ConnectionSerializer(std::ostream& s) : m_stream(s) {}
      
      void operator()(const SConnection& c)
      {
        m_stream << "<connect>\n";
        serialize_plug(m_stream, c.from(), "from");
        serialize_plug(m_stream, c.to(), "to");
        m_stream << "</connect>\n";
      };

    private:
      std::ostream& m_stream;
    };

    //-------------------------------------------------------------------
    class DataSerializer
    {
    public:
      DataSerializer(std::ostream& s) : m_stream(s) {}
      
      void operator()(const SDataItem& di)
      {
        m_stream << "<dataitem> <key>" << di.key() << "</key> " 
                 << "<buf>" << di.value() << "</buf> </dataitem>\n";
      }
        
    private:
      std::ostream& m_stream;
    };

    class NodeSerializer
    {
    public:
      NodeSerializer(std::ostream& s) : m_stream(s) {}
      
      void operator()(const SNode& n)
      {
        m_stream << "<node> <id>" << n.id() << "</id> " 
                 << "<type>" << n.type() << "</type>\n";
        
        m_stream << "<data>\n";
        DataSerializer ds(m_stream);
        std::for_each(n.dataitems().begin(),
                      n.dataitems().end(),
                      ds);
        m_stream << "</data>\n";

        m_stream << "</node>\n";
      }
        
    private:
      std::ostream& m_stream;
    };

    //-------------------------------------------------------------------

    void serialize(std::ostream& s, const SGraph& g)
    {
      s << "<graph>\n";
      s << "<id>"   << g.id() << "</id>\n";
      s << "<name>" << g.name() << "</name>\n";
      s << "<data>\n";
      DataSerializer ds(s);
      std::for_each(g.dataitems().begin(),
                    g.dataitems().end(),
                    ds);
      s << "</data>\n";

      s << "<nodes>\n";
      NodeSerializer ns(s);
      std::for_each(g.nodes().begin(), g.nodes().end(), ns);
      s << "</nodes>\n";

      s << "<connections>\n";
      ConnectionSerializer cs(s);
      std::for_each(g.connections().begin(), g.connections().end(), cs);
      s << "</connections>\n";

      s << "<snapshots>\n";
      SnapshotSerializer ss(s);
      std::for_each(g.snapshots().begin(), g.snapshots().end(), ss);
      s << "</snapshots>\n";
      s << "</graph>\n";
    }

    //-------------------------------------------------------------------
  }
}

