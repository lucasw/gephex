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
#include "utils/stringtokenizer.h"
#include "utils/ilogger.h"

#include "graph.h"
#include "graphserial.h"
#include "controlvalueset.h"

namespace model
{
	
  GraphFileSystem::GraphFileSystem(const std::string& graph_path,
                                   utils::AutoPtr<utils::ILogger>& logger)
    : m_logger(logger)
  {
    utils::StringTokenizer st(graph_path);
    std::string dir;
    while ((dir = st.next(";")) != "")
      {
        m_dirs.push_back(dir);
      }

    if (m_dirs.empty())
      throw std::runtime_error("No graph dir in path");
  }

  GraphFileSystem::~GraphFileSystem()
  {
  }

  void GraphFileSystem::loadGraph(const std::string& graphID, 
				  Graph& destination,
				  const SpecMap& specMap)
  {
    std::map<std::string,std::string>::const_iterator it=
      graphNames2fileNames.find(graphID);
    if (it == graphNames2fileNames.end())
      throw std::runtime_error("no graph with that name "
                               "(GraphFileSystem::loadGraph)");
    
    const std::string fileName = it->second;
    std::ifstream graphfile(fileName.c_str());
    
    if (!graphfile)
      throw std::runtime_error("Could not open file");

    deserializeGraph(graphfile, destination, specMap, *m_logger);
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
	fileName = it->second;
      }
    else
      {
	// create an new filename from the name of the graph
	const std::string& graphName= toSave.getName();
	std::string newFileName;

	// remove forbitten chars from the name to generate the filename
	for(std::string::const_iterator it=graphName.begin();
	    it!=graphName.end();++it)
	  {
	    isnt_allowedFileNameChar pred;
	    if (!pred(*it))
	      {
	        newFileName+=*it;
	      }
	  }
	
	// make the filename unique
	std::string uniqueNewFileName = m_dirs.front() + newFileName;
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
    std::ofstream graphfile(fileName.c_str());

    // check if we can open the file for write mode
    if (graphfile)
      {
	graphfile << toSave;
	if (!graphfile)
	  {
	    throw std::runtime_error("cant write to file");
	  }
      }
    else
      {
	throw std::runtime_error("cant open file");
      }
    
    graphNames2fileNames.insert(std::make_pair(toSave.getID(), fileName));
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
    
    const std::string fileName(it->second);
    graphNames2fileNames.erase(it);

    ValueSetMap::iterator it2 = m_value_sets.find(name);
    if (it2 != m_value_sets.end())
      m_value_sets.erase(it2);
	
    utils::FileSystem::removeFile(fileName);
  }


  GraphFileSystem::IDNameList 
  GraphFileSystem::getNames(const SpecMap& specMap)
  {
    // create list of all subdirs and graph with a DFS
    // no check for cycles implemented

    graphNames2fileNames.clear();
    m_value_sets.clear();

    // initialize
    std::list<std::string> directories;
    std::list<std::string> graphs;
    std::stack<std::string> stack;
    // push all dirs
    for (DirList::const_iterator it = m_dirs.begin();
         it != m_dirs.end(); ++it)
      {
        stack.push(*it); 
      }

    // process
    while ( stack.size() > 0 )
      {
	std::string current(stack.top());
	stack.pop();

	// get the objects in the current dir
	std::list<utils::DirEntry> entries;
	utils::FileSystem::listDir(current, entries);
	
	// push all subdirs
	for (std::list<utils::DirEntry>::const_iterator it = entries.begin();
	     it != entries.end(); ++it)
	  {
	    const std::string fileName(current + "/" + it->getName());
	    switch (it->getType())
	      {
	      case utils::DirEntry::DIRECTORY :
		if (it->getName() != "." && it->getName() != "..")
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

    for (std::list<std::string>::const_iterator graph_it = graphs.begin();
         graph_it != graphs.end(); ++graph_it)
      {
#if (ENGINE_VERBOSITY > 0)
	std::cout << *graph_it << std::endl;
#endif
	try
	  {
	    std::ifstream graphfile( graph_it->c_str() );
	    
	    if(graphfile)
	      {
		Graph graph("noID","noName");
		deserializeGraph(graphfile,graph,specMap,*m_logger,false);
		
		std::map<std::string,std::string>::const_iterator
		  mapit=graphNames2fileNames.find(graph.getID());
		
                // TODO
		if (mapit != graphNames2fileNames.end())
		  throw std::runtime_error("graph id exists "
                                           "(GraphFileSystem::getNames)");

		graphNames2fileNames[graph.getID()] = *graph_it;

		ValueSetList valueSetNames;
		typedef std::map<const std::string,
		  utils::AutoPtr<ControlValueSet> > ValueSetMap;

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
		    
                m_value_sets.insert(std::make_pair(graph.getID(),
                                                   valueSetNames));
                retList.push_back(graphData);
		    
#if (ENGINE_VERBOSITY > 0)
                std::cout << "OK" << std::endl;
#endif
	      }
	    else
	      {
#if (ENGINE_VERBOSITY > 0)
		std::cout << "could not open file" << std::endl;
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

  GraphFileSystem::ValueSetList
  GraphFileSystem::getValueSetList(const std::string& graphID) const
  {
    if (!graphExists(graphID))
      return ValueSetList();

    ValueSetMap::const_iterator it = m_value_sets.find(graphID);
    if (it == m_value_sets.end())
      return ValueSetList();

    return it->second;
  }


  bool GraphFileSystem::graphExists(const std::string& graphName) const
  {
    std::map<std::string,std::string>::const_iterator 
      it = graphNames2fileNames.find(graphName);
	
    return (it != graphNames2fileNames.end());
  }

}
