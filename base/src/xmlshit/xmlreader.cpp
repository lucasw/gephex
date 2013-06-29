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


#include <list>

#include "xmlreader.h"
#include "xmlscanner.h"
#include "xmllistener.h"
#include "../model/moduleinfo.h"

#include <fstream>
#include <stdexcept>

XMLFileReader::XMLFileReader(const std::map<int, ModuleInfo*>& mi, std::ifstream& file)
{
	XMLTokenListener listener(mi, infos, nodes, controls, connections, controlInfos);
	XMLFileScanner scanTeil(listener);

	std::string parseString = "";
	char tmp;

	if(file==0)
	{
		throw std::runtime_error("File not found...uarghs");
	}
	
	while(file.get(tmp))
	{
		parseString += tmp;
	}

	if(!file.eof())
	{
		throw std::runtime_error("Something's wrong with the file!!!");
	}

	scanTeil.scan(parseString);
}

int XMLFileReader::getModuleIDbyName(std::string which)
{
	std::map<std::string, int>::iterator i = infos.begin();	

	while(i!= infos.end())
	{
		if(which == i->first)
		{
			return i->second;
		}
		++i;
	}
	std::string msg = "Modulename not found: ";
	msg += which;
	throw std::runtime_error("Modulename not found: ");
}

/*std::pair<int,int> XMLFileReader::getNodePosition(std::string which)
{
	std::map<std::string, std::pair<int, int> >::iterator i = nodes.begin();

	while(i!= nodes.end())
	{
		if(which == i->first)
		{
			return i->second;
		}
		++i;
	}
	throw std::runtime_error("There is no such node...");
	
}*/

/*int XMLFileReader::getRealNodeIDByFileID(int pos)
{
	std::map<std::string, int>::iterator i = infos.begin();
	std::map<int, std::string>::iterator j = nodeFileIDs.begin();

	while(j!=nodeFileIDs.end())	
	{
		if(pos == j->first)
		{
			while(i!= infos.end())
			{
				if(j->second == i->first)
					return i->second;
				++i;
			}
			throw std::runtime_error("name not in infos??? contact your local suicide box...");
			
		}
		++j;
	}
	throw std::runtime_error("buah..id not found...strange...");
}*/

std::list<NodeInfo> XMLFileReader::getNodes()
{	
	/*std::vector<std::string> nodeNames;
	std::map<std::string, std::pair<int, int> >::iterator i = nodes.begin();
	
	while(i!= nodes.end())
	{
		nodeNames.push_back(i->first);
		++i;
	}
	return nodeNames;*/
	return nodes;
}

/*std::pair<int, int> XMLFileReader::getControlPosition(std::string which)
{
	std::map<std::string, std::pair<int, int> >::iterator i = controls.begin();

	while(i!= controls.end())
	{
		if(which == i->first)
		{
			return i->second;
		}
		++i;
	}
	throw std::runtime_error("There is no such control...");

}*/

/* Die Connnection Ids im file werden nach position vergeben, hier kriegt man daraus den namen */
/*int XMLFileReader::getRealControlIDByFileID(int pos)
{
	std::map<std::string, int>::iterator i = infos.begin();
	std::map<int, std::string>::iterator j = controlFileIDs.begin();

	while(j!=controlFileIDs.end())	
	{
		if(pos == j->first)
		{
			while(i!= infos.end())
			{
				if(j->second == i->first)
					return i->second;
				++i;
			}
			throw std::runtime_error("name not in infos??? contact your local suicide box...");
			
		}
		++j;
	}
	throw std::runtime_error("buah..id not found...strange...");
}*/


std::list<NodeInfo> XMLFileReader::getControls()
{
	/*std::vector<std::string> controlNames;
	std::map<std::string, std::pair<int, int> >::iterator i = controls.begin();
	
	while(i!= controls.end())
	{
		controlNames.push_back(i->first);
		++i;
	}
	return controlNames;*/
	return controls;
}


//des is no ned so guad...
std::map<std::pair<int,int>, std::pair<int,int> > XMLFileReader::getConnections() 
{
	return connections;
}

std::list<ControlInfo> XMLFileReader::getControlInfos() const
{
	return controlInfos;
}
