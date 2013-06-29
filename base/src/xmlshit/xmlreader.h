/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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