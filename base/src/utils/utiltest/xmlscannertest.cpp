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


#include "xmlscannertest.h"
#include "xmlscanner.h"
#include "xmllistener.h"

#include <vector>
#include <moduleinfo.h>
#include <fstream>
#include <iostream>

XMLScannerTest::XMLScannerTest(): EasyTest("XMLScannerTest","")
{}

XMLScannerTest::~XMLScannerTest()
{}

void XMLScannerTest::pre()
{}

void XMLScannerTest::run()
{
		//create a dummy map with a fakie fucking modulewhateverinfo....
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

	//create storage room for the listener
	std::map<std::string, int> infos;
	std::map<std::string, std::pair<int,int> > nodes;
	std::map<int, std::string>  nodeIDs;
	std::map<std::string, std::pair<int,int> > controls;
	std::map<int, std::string> controlIDs;
	std::map<std::pair<int,int>, std::pair<int,int> > conns;
	std::map<std::pair<int,int>, std::pair<int,int> > ctrlconns;

	//create an xmlListener with that dummyinfo
	XMLTokenListener horcher(mi_map, infos, nodes, nodeIDs, controls, controlIDs, conns, ctrlconns);
	XMLFileScanner gucker(horcher);
	std::ifstream ifs("testCorrect.graph");
	if(ifs==0)
		std::cout<<"File not found \n";
	std::string testTextCorrect;	

	char tmp;
	while(ifs.get(tmp))
	{
		testTextCorrect += tmp;
	}

	gucker.scan(testTextCorrect);


	//eine datei ohne <model>
	//std::cout<<"Processing incorrect file 1...\n";
	std::ifstream ifs1("testInCorrect1.graph");
	if(ifs1==0)
		std::cout<<"File not found \n";
	std::string testTextInCorrect1;	
	while(ifs.get(tmp))
	{
		testTextInCorrect1 += tmp;
	}

	try
	{
		gucker.scan(testTextInCorrect1);
	}
	catch(std::runtime_error err)
	{
		//if(err.what() !=  "This is no Ge-Phex Graph file...go fuck your dog!!!")
		//	throw std::runtime_error(err.what());
		//std::cout<<err.what()<<std::endl;
		
	}


	//eine datei ohne </model>, ja, ich weiss, kreativ...
	//std::cout<<"Processing incorrect file 2...\n";
	std::ifstream ifs2("testInCorrect2.graph");
	if(ifs2==0)
		std::cout<<"File not found \n";
	std::string testTextInCorrect2;	
	while(ifs2.get(tmp))
	{
		testTextInCorrect2 += tmp;
	}

	try
	{
		gucker.scan(testTextInCorrect2);
	}
	catch(std::runtime_error err)
	{
		//if(err.what() !=  "File has a wrong finishing tag...wrong format")
		//	throw std::runtime_error(err.what());
		
		//std::cout<<err.what()<<std::endl;
	}

	//eine datei mit fehlender node section
	//std::cout<<"Processing incorrect file 3...\n";
	std::ifstream ifs3("testInCorrect3.graph");
	if(ifs3==0)
		std::cout<<"File not found \n";
	std::string testTextInCorrect3;	


	while(ifs3.get(tmp))
	{
		testTextInCorrect3 += tmp;
	}
	
	try
	{
		gucker.scan(testTextInCorrect3);	
	}
	catch(std::runtime_error err)
	{
		//if(err.what() !=  "File has wrong format...section nodes")
		//	throw std::runtime_error(err.what());
		
		//std::cout<<err.what()<<std::endl;
	}		
}

void XMLScannerTest::post()
{}
