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

#include "xmllistener.h"

#include "utils/stringtokenizer.h"

// doofe abhaengigkeit
#include "gui/point.h"
#include "gui/moduleinfo.h"

#include <sstream>
#include <stdexcept>

//#define VERBOSE_XML_LISTENER
#ifdef VERBOSE_XML_LISTENER
#include <iostream>
#endif


XMLTokenListener::XMLTokenListener(const std::map<int, ModuleInfo*>& infoMap_,
								   std::map<std::string, int>& infos_,
								   std::list<NodeInfo>& nodes_,								
								   std::list<NodeInfo>& controls_,								   
								   std::map<std::pair<int,int>, std::pair<int,int> >& conns,
								   std::list<ControlInfo>& ctrlconns):
infoMap(infoMap_), infos(infos_), nodes(nodes_), 
controls(controls_), connections(conns), ctrlInfos(ctrlconns)
{}

void XMLTokenListener::scannedModuleInfo(std::string& name)
{

	//TODO
	/* Hier muss später ein ModuleInfo-Objekt erzeugt werden und 
	 in der übergebenen Infomap gesucht werden um evtl. dll-Änderungen etc. zu 
	überprüfen*/
	
	std::map<int, ModuleInfo*>::const_iterator i = infoMap.begin();
		
	while(i!= infoMap.end())
	{
		if(i->second->getIdentifier() == name)
		{
			infos[name] = i->first;
			return;
		}
		i++;
	}
	throw std::runtime_error("Module not found...wether module \nhas changed since last run or dll's not been loaded...\n");
}

void XMLTokenListener::scannedNode(std::string& node, int posInFile)
{
	int x,y;
	std::string name;
	std::istringstream s(node);
		s >> name;	
	s >> x;
	s >> y;
	
#ifdef VERBOSE_XML_LISTENER
	std::cout<<"received scannedNode: " << name << ", " << x << ", " << y <<std::endl;
#endif

	NodeInfo ni;
	ni.name = name;
	ni.xPos = x;
	ni.yPos = y;
	ni.fileID  = posInFile;

	nodes.push_back(ni);
}

void XMLTokenListener::scannedControl(std::string& controlElement)
{
  int nodeID;
  int inputIndex;
  std::string widgetType;
  int magicNumber;
  int x;
  int y;

  std::istringstream s(controlElement);
  s >> nodeID;
  s >> inputIndex;
  s >> widgetType;
  s >> magicNumber;
  s >> x;
  s >> y;


  ControlInfo ci;
  ci.nodeFileID = nodeID;
  ci.inputIndex = inputIndex;
  ci.widgetType = widgetType;
  ci.magicNumber = magicNumber;
  ci.xPos = x;
  ci.yPos = y;

  ctrlInfos.push_back(ci);
}

void XMLTokenListener::scannedConnection(std::string& connection)
{
	int id1, out, id2, in;
	std::istringstream s(connection);
	s >> id1;
	s >> out;
	s >> id2;
	s >> in;
#ifdef VERBOSE_XML_LISTENER
	std::cout<<"received scannedConnection: " << id1 << ", " << out << ", " << id2 <<", " << in << std::endl;
#endif
	//hm, hm...woass ned so recht
	std::pair<int,int> n1(id1, out);
	std::pair<int,int> n2(id2, in);
	connections[n1] = n2;
}

/*void XMLTokenListener::scannedControl(std::string& connection)
{
	int id1, type, in, xPos, yPos;
	std::string className;
	std::istringstream s(connection);
	s >> className;
	s >> id1;
	s >> in;
	//s >> id2;
	s >> type;
	s >> xPos;
	s >> yPos;

#ifdef VERBOSE_XML_LISTENER
	std::cout << "received scannedCtrlConnection: " << id1 << ", " << out 
			  << ", "  << in << std::endl;
#endif

	ControlInfo ci;
	ci.moduleClassName = className;
	//ci.controlFileID = id1;
	ci.nodeFileID = id1;
	ci.inputIndex = in;
	ci.widgetType = type;
	ci.xPos = xPos;
	ci.yPos = yPos;

	ctrlInfos.push_back(ci);
}*/

