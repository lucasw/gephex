#include "sequencefilesystem.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "sequence.h"
#include "sequenceserial.h"

#include "utils/filesystem.h"

namespace sequencer
{

  class PutSequenceIntoList
  {
  public:
    PutSequenceIntoList(std::list<std::pair<std::string,std::string> >& n,
			SequenceFileSystem::FileMap& m,
			const std::string& basePath)
      : sequenceNames(n), fileNames(m), m_basePath(basePath) {}

    void operator()(const utils::DirEntry& de)
    {
      if(de.getType() == utils::DirEntry::FILE &&
	 de.getName()!= "." && de.getName() != "..")
	{
	  std::string fileName = m_basePath + de.getName();
	  std::ifstream file(fileName.c_str());
	  if (!file)
	    {
	      //TODO
	      std::cerr << "Cant open file " << fileName << std::endl;
	    }
	  else
	    {					
	      try 
		{
		  std::cerr << "Try to load Sequence " << fileName
			    << std::endl;
		  Sequence doof("doof","dumm");
		  file >> doof;
		  sequenceNames.push_back(std::make_pair(doof.id(),
							 doof.name()));
		  fileNames[doof.id()] = fileName;
		}
	      catch (std::runtime_error& e)
		{
		  //TODO
		  std::cerr << "Error: " << e.what() << std::endl;
		}
	    }
				
	}
    }
  private:
    std::list<std::pair<std::string, std::string> >& sequenceNames;
    SequenceFileSystem::FileMap& fileNames;
    std::string m_basePath;
  };
  SequenceFileSystem::SequenceFileSystem(const std::string& basePath)
    : m_basePath(basePath)
  {
  }

  std::list<std::pair<std::string, std::string> > SequenceFileSystem::getIDsAndNames()
  {

    std::list<std::pair<std::string, std::string> > sequenceNames;
    
    if (!utils::FileSystem::exists(m_basePath))
      {
	utils::FileSystem::makeDir(m_basePath);
      }
    else
      {
	std::list<utils::DirEntry> entries;
	utils::FileSystem::listDir(m_basePath,entries);

	std::for_each(entries.begin(), entries.end(),
		      PutSequenceIntoList(sequenceNames,
					  fileNames,
					  m_basePath));
      }
    return sequenceNames;
  }
		
  void SequenceFileSystem::loadSequence(const std::string id,
					Sequence& destination)
  {
    FileMap::const_iterator 
      it = fileNames.find(id);

    if (it == fileNames.end())
      {
	throw std::runtime_error("no such sequence at "
				 "SequenceFileSystem::loadSequence()");
      }

    std::string fileName = it->second;
    std::ifstream file(fileName.c_str());
    if (!file)
      {
	throw std::runtime_error("cant open file "
				 "SequenceFileSystem::loadSequence()");
      }

    file >> destination;

  }
		
  void SequenceFileSystem::saveSequence(const std::string& id,
					const Sequence& toSave)
  {		

    FileMap::const_iterator 
      it = fileNames.find(id);

    std::string fileName;
    if (it == fileNames.end())
      {
	fileName = m_basePath + id + ".sequence";
      }
    else
      fileName = it->second;


    std::ofstream file(fileName.c_str());
    if (!file)
      {
	throw std::runtime_error("cant open file "
				 "SequenceFileSystem::saveSequence()");
      }

    file << toSave;
  }
		
  void SequenceFileSystem::deleteSequence(const std::string& id)
  {
    FileMap::iterator it = fileNames.find(id);

    if ( it == fileNames.end() )
      {
	return;
	//throw std::runtime_error("Sequence doesnt exist at "
	//	"SequenceFileSystem::deleteSequence()");
      }

    std::string fileName = it->second;
    fileNames.erase(it);

    utils::FileSystem::removeFile(fileName);
  }
  //bool SequenceExists(const std::string& SequenceName) const;
		

} // end of namespace
