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

  class GraphFileSystem {
  public:
    //typedef std::map<const std::string,utils::AutoPtr<IModuleClassSpec> > SpecMap;

    typedef std::list<std::pair<std::pair<std::string, std::string>,
      std::list<std::pair<std::string, std::string> > > > IDNameList;

    GraphFileSystem(const std::string& basepath);
    ~GraphFileSystem();

    IDNameList getNames(const SpecMap& specMap);

    void loadGraph(const std::string graphName, Graph& destination,
		   const SpecMap& specMap);

    void saveGraph(const Graph& toSave);

    void deleteGraph(const std::string& name);

    bool graphExists(const std::string& graphName) const;

    /*    void rename(const std::string& graphName,
	  const std::string& newGraphName);*/

  private:
    std::string basePath;
    std::map<std::string,std::string> graphNames2fileNames;
    //const SpecMap& specMap;
  };

}

#endif
