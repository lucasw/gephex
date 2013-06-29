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

#include "xmlreadertest.h"
#include "xmlreader.h"
#include "moduleinfo.h"

#include <vector>
#include <map>
#include <fstream>

XMLReaderTest::XMLReaderTest(): EasyTest("XMLReaderTest","")
{}

XMLReaderTest::~XMLReaderTest()
{}

void XMLReaderTest::pre()
{}

void XMLReaderTest::run()
{
	//create a dummy map with a fakie fucking modulewhateverinfo....actually this infomap
	//fits exactly the file 'testCorrect.graph'...bah, it's 05:19, i'm tired....
	std::vector<std::pair<std::string, std::string> > outs(1);
	std::vector<std::pair<std::string, std::string> > ins(0);
	std::pair<std::string, std::string> outpair("typ_string", "String");
	outs[0] = outpair;
	
	//Xpm dummy(dummyXpm, strlen(dummyXpm)+1);
	ModuleInfo* mi = new ModuleInfo("mod_stringModule", "String", 
								    ins, outs, true);

	
	std::vector<std::pair<std::string, std::string> > outs2(0);
	std::vector<std::pair<std::string, std::string> > ins2(1);
	std::pair<std::string, std::string> inpair("typ_framebuffer", "Bild");
	ins2[0] = inpair; 
	ModuleInfo* mi2 = new ModuleInfo("mod_glOutputModule", "GLoutput" , 
								    ins, outs, false);

	std::vector<std::pair<std::string, std::string> > outs3(1);
	std::vector<std::pair<std::string, std::string> > ins3(3);
	
	std::pair<std::string, std::string> inpair2("typ_number","Zahl");
	
	ins3[0] = inpair2; 
	ins3[1] = inpair2;
	ins3[2] = inpair;

	outs3[0] = inpair;

	ModuleInfo* mi3 = new ModuleInfo("mod_tunnelModule", "Tunnel" , 
								    ins, outs, false);

	
	std::map<int, ModuleInfo*> mi_map;
	mi_map[0] = mi;
	mi_map[1] = mi2;	
	mi_map[2] = mi3;


	/* this test simly checks an example file named 'testCorrect.graph'
	   see that file for further explanation */
	std::ifstream file("testCorrect.graph");
	
	XMLFileReader parsingSux(mi_map, file);

	int tmp = parsingSux.getModuleIDbyName("mod_stringModule");
	if(tmp!=0) throw std::runtime_error("Bähm 0...");
	tmp = parsingSux.getModuleIDbyName("mod_glOutputModule");
	if(tmp!=1) throw std::runtime_error("Bähm 1...");
	tmp = parsingSux.getModuleIDbyName("mod_tunnelModule");
	if(tmp!=2) throw std::runtime_error("Bähm 2...");

	std::vector<std::string> nodes = parsingSux.getNodes();
	std::pair<int,int> pos = parsingSux.getNodePosition(nodes[1]);
	if(pos.first!=249 || pos.second!=151)
		throw std::runtime_error("Got a wrong position here (1)");
	pos = parsingSux.getNodePosition(nodes[0]);
	if(pos.first!=333 || pos.second!=125)
		throw std::runtime_error("Got a wrong position here (2)");
	

	
	std::vector<std::string> controls = parsingSux.getControls();
	pos = parsingSux.getControlPosition(controls[0]);
	if(pos.first != 37 || pos.second != 49)
		throw std::runtime_error("Got a wrong position here (3)");


	int id;
	id = parsingSux.getRealNodeIDByFileID(0);
	//should be the tunnel_module
	if(id!=2)
		throw std::runtime_error("Wrong id...");
	id = parsingSux.getRealNodeIDByFileID(1);
	if(id!=1)
		throw std::runtime_error("Wrong id...");
	id = parsingSux.getRealControlIDByFileID(0);
	if(id!=0)
		throw std::runtime_error("Wrong id...");
}

void XMLReaderTest::post()
{}