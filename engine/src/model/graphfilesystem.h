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

#ifndef INCLUDED_GRAPHFILESYSTEM_H
#define INCLUDED_GRAPHFILESYSTEM_H

#include <string>
#include <map>
#include <list>

#include "utils/autoptr.h"
#include "specmap.h"

namespace utils
{
  class ILogger;
}
class IModuleClassSpec;

namespace model
{
  class Graph;

  /**
   * This component interfaces the graphmodel with the filesystem on the 
   * maschine that is running the engine.
   */
  class GraphFileSystem 
    {
    public:
   
      typedef std::list<std::pair<std::string, std::string> > ValueSetList;
      
      /**
       * \todo change this ugly type
       */
      typedef std::list<std::pair<std::pair<std::string, std::string>,
	ValueSetList> > IDNameList;
      
      /**
       * Creates a new Filesystem object.
       *
       * \param basepath This is the root directory for graph hierarchy.
       */
      GraphFileSystem(const std::string& graph_path,
                      utils::AutoPtr<utils::ILogger>& logger);

      /**
       * Destroys the Object
       */
      ~GraphFileSystem();

      /**
       * Creates a list of directorys and graphs in these.
       *
       * \todo remove the specMap parameter
       * \todo dont load all graphs at this time
       * \todo create ids by the filename and dont use the id stored in 
       *       the file 
       */
      IDNameList getNames(const SpecMap& specMap);

      /**
       * must not be called before getNames
       */
      ValueSetList getValueSetList(const std::string& graphID) const;
      
      /**
       * Loads a graph from the filesystem
       *
       * \param graphName Name of the graph to load
       * \param destination assign it to this graph instance
       * \param specMap
       */
      void loadGraph(const std::string& graphName, Graph& destination,
		     const SpecMap& specMap);

      /**
       * Writes the value of this graph back to the filesystem
       *
       * \param toSave Graph to write back to disc
       */
      void saveGraph(const Graph& toSave);

      /**
       * Deletes a graph from the filesystem
       *
       * \param Name of the graph to delete
       */
      void deleteGraph(const std::string& name);
      
      /**
       * Checks if a graph with that name exists
       *
       * \param graphName Name of the Graph to search
       * \returns true if the graph is in the file hierarchie
       */
      bool graphExists(const std::string& graphName) const;
      
    private:
      utils::AutoPtr<utils::ILogger> m_logger;      
      typedef std::list<std::string> DirList;
      DirList m_dirs;
      
      /**
       * Maps the Name of the Graphs to the files on the disc
       */
      std::map<std::string,std::string> graphNames2fileNames;
      
      typedef std::map<std::string, ValueSetList> ValueSetMap;
      ValueSetMap m_value_sets;
    };
}

#endif
