#ifndef INCLUDED_FILE_INFOS_H
#define INCLUDED_FILE_INFOS_H

#include <string>

struct NodeInfo
{
	std::string name;
	int fileID;
	int xPos;
	int yPos;
};

struct ControlInfo
{	
	int nodeFileID;
	int inputIndex;
	std::string widgetType;
  int magicNumber;
	int xPos;
	int yPos;
};

#endif
