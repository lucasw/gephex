#ifndef GRAPHFILESYSTEM_H
#define GRAPHFILESYSTEM_H

#include <string>
#include <map>
#include <list>

#include "utils/autoptr.h"
#include "specmap.h"

class IModuleClassSpec;

namespace model
{

  class Graph;

  /**
   * This component interfaces the graphmodel with the filesystem on the maschine 
   * running the engine.
   */
  class GraphFileSystem 
    {
    public:
   
      /**
       * \todo change this ugly type
       */
      typedef std::list<std::pair<std::pair<std::string, std::string>,
	std::list<std::pair<std::string, std::string> > > > IDNameList;

      /**
       * Creates a new Filesystem object.
       *
       * \param basepath This is the root directory for graph hierarchy.
       */
      GraphFileSystem(const std::string& basepath);

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
       * Loads a graph from the filesystem
       *
       * \param graphName Name of the graph to load
       * \param destination assign it to this graph instance
       * \param specMap
       */
      void loadGraph(const std::string graphName, Graph& destination,
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

      /**
       * renames a graph in the filesystem
       */
      // void rename(const std::string& graphName, const std::string& newGraphName);

    private:
      
      /**
       * Root directory of the graph subdir e.g. "/home/user/.gephex/graphs"
       */
      std::string basePath;

      /**
       * Maps the Name of the Graphs to the files on the disc
       */
      std::map<std::string,std::string> graphNames2fileNames;
    };
  
}

#endif
