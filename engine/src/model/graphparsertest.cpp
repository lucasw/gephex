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

#include "graphparsertest.h"

#include <iostream>
#include <sstream>

#include "graphparser.h"

GraphParserTest::GraphParserTest()
  : EasyTest("GraphParserTest","")
{
}

GraphParserTest::~GraphParserTest()
{

}

void GraphParserTest::pre() throw(std::runtime_error)
{

}

template <typename T>
static void check_equal(const std::string& text,
                        const T& is,
                        const T& should)
{
  if (is != should)
    {
      std::ostringstream o;
      o << "check_equal failed:\n" << text << " should be '" << should
        << "' but is '" << is << "'";
      throw std::runtime_error(o.str().c_str());
    }
}

static void check_equal_dataitem(const model::gparser::SDataItem& d,
                                 const std::string& key,
                                 const std::string& value)
{
  check_equal<std::string>("dataitem.key()", d.key(), key);
  check_equal<std::string>("dataitem.value()", d.value(), value);
}

static void check_equal_plug(const model::gparser::SPlug& p,
                                   const std::string& ni,
                                   const std::string& pi)
{
  check_equal<std::string>("p.node_id()", p.node_id(), ni);
  check_equal<std::string>("p.plug_id()", p.plug_id(), pi);
}

static void check_equal_connection(const model::gparser::SConnection& c,
                                   const std::string& fni,
                                   const std::string& fpi,
                                   const std::string& tni,
                                   const std::string& tpi)
{
  check_equal_plug(c.from(), fni, fpi);
  check_equal_plug(c.to(), tni, tpi);
}

static void check_equal_value(const model::gparser::SValue& v,
                              const std::string& ni,
                              const std::string& pi,
                              const std::string& val)
{
  check_equal_plug(v.plug(), ni, pi);
  check_equal<std::string>("value.value()", val, v.value());
}

static void check_graph1(const model::gparser::SGraph& g)
{
  check_equal<std::string>("g.id()", g.id(), "gid");
  check_equal<std::string>("g.name()", g.name(), "hans");
  
  std::list<model::gparser::SNode> nodes = g.nodes();
  check_equal<int>("#nodes", nodes.size(), 1);

  model::gparser::SNode n1 = *nodes.begin();
  check_equal<std::string>("n1.id()", n1.id(), "n1");
  check_equal<std::string>("n1.type()", n1.type(), "t1");

  std::list<model::gparser::SDataItem> dat = n1.dataitems();
  check_equal<int>("#dataitems", dat.size(), 2);
  std::list<model::gparser::SDataItem>::const_iterator dat_it = dat.begin();
  check_equal_dataitem(*dat_it,     "k1", "HARR");
  check_equal_dataitem(*(++dat_it), "k2", "PAFF");

  std::list<model::gparser::SConnection> connections = g.connections();
  check_equal<int>("#connections", connections.size(), 1);
  model::gparser::SConnection conn = connections.front();
  check_equal_connection(conn, "n1", "p1", "n2", "p2");

  std::list<model::gparser::SSnapshot> snapshots = g.snapshots();
  check_equal<int>("#snapshots", snapshots.size(), 1); 
  model::gparser::SSnapshot snap = snapshots.front();

  std::list<model::gparser::SValue> values = snap.values();
  check_equal<int>("#values", values.size(), 2); 
  std::list<model::gparser::SValue>::const_iterator val_it = values.begin();
  check_equal_value(*val_it, "n1", "p1", "das ist das haus vom nikolaus");
  check_equal_value(*(++val_it), "n2", "p2", "brat bratfett mit salamo ohne");
}

std::string graph_text 
    = "<graph> <id>gid</id> <name>hans</name>\n"
    "<nodes>\n"
    "  <node> <id>n1</id> <type>t1</type>\n"
    "    <data>\n"
    "       <dataitem> <key>k1</key> <buf>HARR</buf> </dataitem>\n"
    "       <dataitem> <key>k2</key> <buf>PAFF</buf> </dataitem>\n"
    "    </data>\n"
    "  </node>\n"
    "</nodes>\n"

    "<connections>\n"
    "  <connect>\n"
    "     <from> <node_id>n1</node_id> <plug_id>p1</plug_id> </from>\n"
    "     <to>   <node_id>n2</node_id> <plug_id>p2</plug_id> </to>\n"
    "  </connect>\n"
    "</connections>\n"

    "<snapshots>\n"
    "  <snapshot> <id>s1</id> <name>peter</name>\n"
    "    <values>\n"
    "      <value>\n"
    "        <plug> <node_id>n1</node_id> <plug_id>p1</plug_id> </plug>\n"
    "        <buf>das ist das haus vom nikolaus</buf>\n"
    "      </value>\n"
    "      <value>\n"
    "        <plug> <node_id>n2</node_id> <plug_id>p2</plug_id> </plug>\n"
    "        <buf>brat bratfett mit salamo ohne</buf>\n"
    "      </value>\n"
    "    </values>\n"
    "  </snapshot>\n"
    "</snapshots>\n"

    "</graph>\n";

static void test1()
{ 
  model::gparser::SGraph g = model::gparser::parse(graph_text);

  check_graph1(g);
}

void test2()
{
  model::gparser::SGraph g = model::gparser::parse(graph_text);
  
  std::ostringstream os;
  model::gparser::serialize(os, g);
  
  //  std::cout << os.str() << "\n";
  g = model::gparser::parse(os.str());

  check_graph1(g);
}
void GraphParserTest::run() throw(std::runtime_error)
{
  test1();
  test2();
}

void GraphParserTest::post() throw(std::runtime_error)
{

}
