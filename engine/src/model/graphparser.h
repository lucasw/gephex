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

#ifndef INCLUDED_GRAPH_PARSER_H
#define INCLUDED_GRAPH_PARSER_H

#include <list>
#include <string>

namespace model
{
  namespace gparser  
  {
    class SPlug
    {
    public:
      SPlug() {}
      SPlug(const std::string& node_id,
	    const std::string& plug_id);

      std::string node_id() const;
      std::string plug_id() const;

    private:
      std::string m_node_id;
      std::string m_plug_id;
    };


    class SValue
    {
    public:
      SValue() {}
      SValue(const SPlug& plug, std::string& value);

      const SPlug& plug() const;
      const std::string& value() const;

    private:
      SPlug m_plug;
      std::string m_value;
    };

    class SSnapshot
    {
    public:
      SSnapshot() {}
      SSnapshot(const std::string& id,
		const std::string& name,
		std::list<SValue>& values);

      std::string id() const;
      std::string name() const;

      const std::list<SValue>& values() const;

    private:
      std::string m_id;
      std::string m_name;
      std::list<SValue> m_values;
    };

    class SConnection
    {
    public:
      SConnection() {}
      SConnection(const SPlug& from, const SPlug& to);

      const SPlug& from() const;
      const SPlug& to() const;

    private:
      SPlug m_from;
      SPlug m_to;
    };

    class SDataItem
    {
    public:
      SDataItem() {};
      SDataItem(const std::string& key,
		std::string& value);

      std::string key() const;
      const std::string& value() const;

    private:
      std::string m_key;
      std::string m_value;
    };

    class SNode
    {
    public:
      SNode() {};
      SNode(const std::string& id,
	    const std::string& type,
	    std::list<SDataItem>& dataitems);

      std::string id() const;
      std::string type() const;
      const std::list<SDataItem>& dataitems() const;
    private:
      std::string m_id;
      std::string m_type;
      std::list<SDataItem> m_dataitems;
    };

    class SGraph
    {
    public:
      SGraph(const std::string& id,
	     const std::string& name,
             std::list<SDataItem>& dataitems,
	     std::list<SNode>& nodes,
	     std::list<SConnection>& connections,
	     std::list<SSnapshot>& snapshots);

      std::string id() const;
      std::string name() const;

      const std::list<SDataItem>& dataitems() const;
      const std::list<SNode>& nodes() const;
      const std::list<SConnection>& connections() const;
      const std::list<SSnapshot>& snapshots() const;

    private:
      std::string m_id;
      std::string m_name;
      std::list<SDataItem> m_dataitems;
      std::list<SNode> m_nodes;
      std::list<SConnection> m_connections;
      std::list<SSnapshot> m_snapshots;
    };

    const SGraph parse(const std::string& text);

    void serialize(std::ostream& s, const SGraph& g);
  }
}
#endif
