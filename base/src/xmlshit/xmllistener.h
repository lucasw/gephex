#ifndef __INCLUDED_XMLLISTENER_H__
#define __INCLUDED_XMLLISTENER_H__

#include <map>
#include <string>
#include <list>

#include "fileinfos.h"

class ModuleInfo;

class XMLTokenListener
{
private:
	const std::map<int, ModuleInfo*>& infoMap; 
	std::map<std::string, int>& infos;
	std::list<NodeInfo>& nodes;
	
	std::list<NodeInfo>& controls;
	
	std::map<std::pair<int,int>, std::pair<int,int> >& connections;
	std::list<ControlInfo>& ctrlInfos;
public:
	XMLTokenListener(const std::map<int, ModuleInfo*>& infoMap_,
					 std::map<std::string, int>& infos_,
					 std::list<NodeInfo>& nodes_,					 
					 std::list<NodeInfo>& controls_,				
					 std::map<std::pair<int,int>, std::pair<int,int> >& conns,
					 std::list<ControlInfo>& ctrlconns);
	void scannedModuleInfo(std::string&);
	void scannedNode(std::string&, int pos);
	void scannedControl(std::string&);
	void scannedConnection(std::string&);
	//void scannedControl(std::string&);
};	

#endif
