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
