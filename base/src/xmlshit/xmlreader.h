#ifndef __INCLUDED_XMLREADER_H__
#define __INCLUDED_XMLREADER_H__

#include <map>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#include "fileinfos.h"


class ModuleInfo;

class XMLFileReader
{
private:
	
	std::map<std::string, int> infos;
	std::list<NodeInfo> nodes;
	std::list<NodeInfo> controls;
	std::map<std::pair<int,int>, std::pair<int,int> > connections;
	std::list<ControlInfo> controlInfos;

public:
	XMLFileReader(const std::map<int, ModuleInfo*>& infoMap_, std::ifstream& file);
	
	int getModuleIDbyName(std::string);
	std::pair<int,int> getNodePosition(std::string which);
	std::list<NodeInfo> getNodes();
	std::pair<int,int> getControlPosition(std::string which);
	std::list<NodeInfo> getControls();
	std::map<std::pair<int,int>, std::pair<int,int> > getConnections();
	std::list<ControlInfo> getControlInfos() const;
};

#endif