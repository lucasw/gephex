#include "graphfilesystem.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <stack>

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include "utils/filesystem.h"

#include "graph.h"
#include "graphserial.h"

#include "controllvalueset.h"

#include <iostream>

namespace model
{
	
  GraphFileSystem::GraphFileSystem(const std::string& basePath_)
    : basePath(basePath_)
  {
    // create root dir if it doesn't already exist
    if (!utils::FileSystem::exists(basePath))
      {
	utils::FileSystem::makeDir(basePath);
      }
  }

  GraphFileSystem::~GraphFileSystem()
  {
  }

  void GraphFileSystem::loadGraph(const std::string graphID, 
				  Graph& destination,
				  const SpecMap& specMap)
  {
    std::map<std::string,std::string>::const_iterator it=
      graphNames2fileNames.find(graphID);
    if (it==graphNames2fileNames.end())
      throw std::runtime_error("no graph with that name(GraphFileSystem::loadGraph)");

    std::string fileName=basePath + "/" + it->second;
    std::ifstream graphfile(fileName.c_str());
    
    deserializeGraph(graphfile,destination,specMap);
    //graphfile >> destination;
  }

  namespace
  {

    // checks for a invalid char in a filename
    class isnt_allowedFileNameChar
    {
    public:
      bool operator() (const char& ch) const
      {
	if ( (ch>='a'&&ch<='z') || (ch>='0'&&ch<='9') || (ch=='_') )
	  return false;
	else
	  return true;
      }
    };
  }

  void GraphFileSystem::saveGraph(const Graph& toSave)
  {
    std::string fileName;

    //check if this graph has already a filename
    std::map<std::string,std::string>::const_iterator it=
      graphNames2fileNames.find(toSave.getID());
    if (it!=graphNames2fileNames.end())
      {
	// use the old filename
	fileName=(it->second);
      }
    else
      {
	// create an new filename from the name of the graph
	const std::string& graphName= toSave.getName();
	std::string newFileName;

	// remove forbitten chars from the name to generate the filename
        //#ifndef _MSC_VER
        //       	std::remove_copy_if(graphName.begin(),graphName.end(),
        //			    std::back_inserter(newFileName),
        //			    isnt_allowedFileNameChar());
        //#else
	for(std::string::const_iterator it=graphName.begin();
	      it!=graphName.end();++it)
	  {
	    isnt_allowedFileNameChar pred;
	    if (!pred(*it))
	      {
	        newFileName+=*it;
	      }
	  }
        //#endif


	//make unique
	std::string uniqueNewFileName = newFileName;
	int index=0;
	while (utils::FileSystem::exists(uniqueNewFileName))
	  {
	    ++index;
	    std::ostringstream indexStream;
	    indexStream << index;
	    uniqueNewFileName=newFileName+indexStream.str();
	  }
	fileName=uniqueNewFileName;
      }

    // create or overwrite the file
    std::string pathFileName=basePath+"/"+fileName;
    std::ofstream graphfile(pathFileName.c_str());

    // check if we can open the file for write mode
    if (graphfile)
      {
	graphfile << toSave;
	if (!graphfile)
	  {
	    std::cerr << "cant write to file:" << fileName.c_str() <<std::endl;
	    throw std::runtime_error("cant write to file");
	  }
      }
    else
      {
	std::cerr << "cant open file:" << fileName.c_str() << std::endl;
	throw std::runtime_error("cant open file");
      }
    
    graphNames2fileNames[toSave.getID()]=fileName;
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
	
    std::string fileName = basePath+"/"+it->second;
    graphNames2fileNames.erase(it);
	
    utils::FileSystem::removeFile(fileName);
  }


  GraphFileSystem::IDNameList 
  GraphFileSystem::getNames(const SpecMap& specMap)
  {
    // create list of all subdirs and graph with a DFS
    // no check for cycles implemented

    // initialize
    std::list<std::string> directories;
    std::list<std::string> graphs;
    std::stack<std::string> stack;
    // start in the base dir
    stack.push(""); 

    // process
    while ( stack.size() > 0 )
      {
	std::string current=stack.top();
	stack.pop();

	// get the objects in the current dir
	std::list<utils::DirEntry> entries;
	utils::FileSystem::listDir(basePath+"/"+current,entries);
	
	// push all subdirs
	for (std::list<utils::DirEntry>::const_iterator
	       it=entries.begin();it!=entries.end();++it)
	  {
	    std::string fileName=current + "/" + it->getName();
	    switch (it->getType())
	      {
	      case utils::DirEntry::DIRECTORY :
		if (it->getName()!= "." && it->getName() != "..")
		  {
		    stack.push(fileName);
		    directories.push_back(fileName);
		  }
		break;

	      case utils::DirEntry::FILE :
		graphs.push_back(fileName);
		break;
	      }
	  }
	

      }
    
    // create list of all files
    IDNameList retList;

    for (std::list<std::string>::const_iterator
	   graph_it=graphs.begin();graph_it!=graphs.end();++graph_it)
      {
	std::cout << *graph_it << std::endl;
	try
	  {
	    std::ifstream graphfile((basePath + "/" + (*graph_it)).c_str());
	    
	    if(graphfile)
	      {
		Graph graph("noID","noName");
		deserializeGraph(graphfile,graph,specMap,false);
		
		std::map<std::string,std::string>::const_iterator
		  mapit=graphNames2fileNames.find(graph.getID());
		    
		if (mapit!=graphNames2fileNames.end())
		  throw std::runtime_error("graph id exists "
					       "(GraphFileSystem::getNames)");
		     
		graphNames2fileNames[graph.getID()] = *graph_it;
		
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
