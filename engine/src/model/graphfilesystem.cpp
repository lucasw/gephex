#include "graphfilesystem.h"

#include <fstream>
#include <stdexcept>

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include "utils/filesystem.h"

#include "graph.h"
#include "graphserial.h"

#include "controllvalueset.h"

namespace model
{
	
  GraphFileSystem::GraphFileSystem(const std::string& basePath_)
    : basePath(basePath_)
  {
  }

  GraphFileSystem::~GraphFileSystem()
  {
  }

  void GraphFileSystem::loadGraph(const std::string graphID, Graph& destination,
				  const SpecMap& specMap)
  {
    std::map<std::string,std::string>::const_iterator it=
      graphNames2fileNames.find(graphID);
    if (it==graphNames2fileNames.end())
      throw std::runtime_error("no graph with that name(GraphFileSystem::loadGraph)");
    std::ifstream graphfile(it->second.c_str());
    
    deserializeGraph(graphfile,destination,specMap);
    //graphfile >> destination;
  }

  void GraphFileSystem::saveGraph(const Graph& toSave)
  {
    std::string fileName;
    std::map<std::string,std::string>::const_iterator it=
      graphNames2fileNames.find(toSave.getID());
    if (it!=graphNames2fileNames.end())
      fileName=(it->second);
    else
      fileName=basePath+toSave.getID();
    std::ofstream graphfile(fileName.c_str());
    graphfile << toSave;
  }

  void GraphFileSystem::deleteGraph(const std::string& name)
  {
    std::map<std::string,std::string>::iterator 
      it = graphNames2fileNames.find(name);

    if ( it == graphNames2fileNames.end() )
      {
	return;
	//		throw std::runtime_error("Graph doesnt exist at "
	//	"GraphFileSystem::deleteSequence()");
      }
	
    std::string fileName = it->second;
    graphNames2fileNames.erase(it);
	
    utils::FileSystem::removeFile(fileName);
  }

  GraphFileSystem::IDNameList
  GraphFileSystem::getNames(const SpecMap& specMap)
  {
    // get filenames fromBasepath
    std::list<utils::DirEntry> entries;
    utils::FileSystem::listDir(basePath,entries);
    IDNameList retList;
    for (std::list<utils::DirEntry>::const_iterator
	   it=entries.begin();it!=entries.end();++it)
      {
	if(it->getType() == utils::DirEntry::FILE &&
	   it->getName()!= "." && it->getName() != "..")
	  {
#if (ENGINE_VERBOSITY > 0)
	    std::cout << "loading graph: " << it->getName() << " - ";
#endif
	    try
	      {
		std::ifstream graphfile((basePath+it->getName()).c_str());
		if(graphfile)
		{
			Graph graph("noID","noName");
			deserializeGraph(graphfile,graph,specMap,false);
				
			std::map<std::string,std::string>::const_iterator
				mapit=graphNames2fileNames.find(graph.getID());

			if (mapit!=graphNames2fileNames.end())
				throw std::runtime_error("graph id exists "
					   "(GraphFileSystem::getNames)");

			graphNames2fileNames[graph.getID()] = basePath
				+ it->getName();
				
			std::list<std::pair<std::string,std::string> > valueSetNames;
			typedef std::map<const std::string,
			utils::AutoPtr<ControllValueSet> > ValueSetMap;
				
			for(ValueSetMap::const_iterator
			      it = graph.getValueSetMap().begin();
			    it != graph.getValueSetMap().end(); ++it)
			  {
			    valueSetNames.push_back(std::make_pair(it->first,
								   it->second->getName()));
						    
			  }
			std::pair<std::pair<std::string,std::string>,
			  std::list<std::pair<std::string, std::string> > >
			  graphData(std::make_pair(graph.getID(),graph.getName()),
			    valueSetNames);
		    
			retList.push_back(graphData);

#if (ENGINE_VERBOSITY > 0)
	    std::cout << "OK" << std::endl;
#endif
		}
		else
		{
#if (ENGINE_VERBOSITY > 0)
			std::cout << "FAIL" << std::endl;
#endif
		}
	      } 
	    catch(std::exception& e)
	      {
#if (ENGINE_VERBOSITY > 0)
			std::cout << "FAIL : " << e.what()<< std::endl;
#endif
	      }
	  }
      }
    return retList;
  }
  bool GraphFileSystem::graphExists(const std::string& graphName) const
  {
    std::map<std::string,std::string>::const_iterator 
      it = graphNames2fileNames.find(graphName);
	
    return (it != graphNames2fileNames.end());
  }

  /*
    void GraphFileSystem::rename(const std::string& graphName,
    const std::string& newGraphName)
    {
    std::map<std::string,std::string>::iterator 
    it = graphNames2fileNames.find(graphName);
	
    if (it == graphNames2fileNames.end())
    throw std::runtime_error("No such Graph at "
    "GraphFileSystem::rename()");
	
    std::string fileName = it->second;
	
    graphNames2fileNames.erase(it);
	
    graphNames2fileNames[newGraphName] = fileName;
	
    }
  */
}
