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

#ifndef INCLUDED_GRAPH_H
#define INCLUDED_GRAPH_H

#include <map>
#include <vector>
#include <list>
#include <string>
#include <iosfwd>

#include "utils/autoptr.h"
#include "utils/buffer.h"

class IModuleClassSpec;

namespace model
{
  class GraphNode;
  class GraphConnection;
  class ControlValueSet;

  class Graph
    {
    public:
      typedef const std::string ControlValueSetID; 
      typedef int ModuleID;
      typedef utils::AutoPtr< ControlValueSet > ControlValueSetPtr; 
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
      
      /** 
       * Deletes all Modules and Connections. 
       */
      void clear();

      // graph data
      void setData(int type, const utils::Buffer& buf);
      void unSetData(int type);

      // ModuleData
      void setModuleData(ModuleID moduleID,int type,const utils::Buffer& buf);
      void unSetModuleData(ModuleID moduleID,int type);

      /** 
       * returns a list of set moduleDatas 
       **/
      std::list<int> moduleDataList(ModuleID moduleID) const;

      // ControlValues
      void newControlValueSet(ControlValueSetID&, const std::string& name);

      void setControlValue(ControlValueSetID& snapShotID, 
			   ModuleID nodeID,
			   int inputIndex, 
			   const utils::Buffer& newValue);

      void copyControlValueSet(ControlValueSetID& snapID,
				ControlValueSetID& newID,
				const std::string& newSnapName);

      void renameControlValueSet(ControlValueSetID& snapID,
				  const std::string& newSnapName);

      void deleteControlValueSet(const std::string& snapID);
      const ValueSetMap& getValueSetMap() const;

      std::string getOutputID(int moduleID, int outputIndex) const;
      std::string getInputID(int moduleID, int inputIndex) const;

      const std::map<int, utils::Buffer>& data() const;

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

      std::map<int, utils::Buffer> m_data;
    };  
}

#endif
