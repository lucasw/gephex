#ifndef INCLUDED_PLUG_INFO_H
#define INCLUDED_PLUG_INFO_H

#include <string>
#include <map>

struct PlugInfo
{
	std::string name;
	std::string type;
	std::map<std::string,std::string> params;
};


#endif
