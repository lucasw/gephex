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

#include "loadmoduletest.h"

#include "dllloader/dllloader.h"

#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/itypeclassinforeceiver.h"
#include "interfaces/itypeclassreceiver.h"


#include "engine/moduleclassspec.h"
#include "engine/moduleinfo.h"

#include <stdexcept>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>


LoadModuleTest::LoadModuleTest()
  : EasyTest("LoadModuleTest","")
{
}

LoadModuleTest::~LoadModuleTest()
{
}

class DummyModuleClassSpecReceiver: public IModuleClassSpecReceiver
{
public:
	virtual ~DummyModuleClassSpecReceiver() {};
	virtual void moduleClassLoaded(int moduleClassID,const ModuleClassSpec&);
};

void DummyModuleClassSpecReceiver::moduleClassLoaded(int moduleClassID,const ModuleClassSpec& specco)
{
	const std::vector<int>& ins = specco.inputs();
	const std::vector<int>& outs = specco.outputs();
	int moduleClassID_ = specco.moduleClassID();
	
	if(ins.size() != 2) throw std::runtime_error("Anzahl inputs nicht zwei!!!");
	if(ins[0] != ins[1]) throw std::runtime_error("Inputs sind nicht gleich!!!");
	if(outs.size() != 1) throw std::runtime_error("Anzahl outputs nicht eins!!!");
	if(ins[0] != outs[0]) throw std::runtime_error("ins[0] != outs[0]");
	if(moduleClassID_  != moduleClassID) throw std::runtime_error("Übergebene modClassID ungleich der, die im spec steht...");
}

class DummyModuleClassInfoReceiver: public IModuleClassInfoReceiver
{
public:
	virtual void moduleClassLoaded(int moduleClassID,const ModuleInfo&);
};

void DummyModuleClassInfoReceiver::moduleClassLoaded(int moduleClassID, const ModuleInfo& mi)
{
	const char* soll = " { group=[Shit]; gui_name=[Adder]; identifier=[mod_addNumbers]; inputs=[2 Summand1:typ_number Summand2:typ_number ]; outputs=[1 Summe:typ_number ]; type=[xpm];  } ";


	if (strcmp(mi.getData(),soll) != 0)
		throw std::runtime_error(mi.getData());
}


class DummyModuleClassReceiver: public IModuleClassReceiver
{
public:
	
	virtual void moduleClassLoaded(int moduleClassID,const IModuleClass& moduleClass) {};
};

class DummyTypeClassReceiver: public ITypeClassReceiver
{
public:
	virtual ~DummyTypeClassReceiver(){};
	virtual void typeClassLoaded(int typeClassID, const ITypeClass& typeClass) {};
};

class DummyTypeClassInfoReceiver: public ITypeClassInfoReceiver
{
public:
	virtual ~DummyTypeClassInfoReceiver() {};
	virtual void typeClassLoaded(int typeClassID, const TypeInfo& info_) {};
};

void LoadModuleTest::pre() throw (std::runtime_error)
{
}

void LoadModuleTest::run() throw (std::runtime_error)
{
	DummyModuleClassReceiver classReceiver;
	DummyModuleClassInfoReceiver infoReceiver;
	DummyModuleClassSpecReceiver specReceiver;
	DummyTypeClassReceiver tclassReceiver;
	DummyTypeClassInfoReceiver tinfoReceiver;

	dllloader::DllLoader loader;

	loader.registerModuleClassReceiver(classReceiver);
	loader.registerModuleClassInfoReceiver(infoReceiver);
	loader.registerModuleClassSpecReceiver(specReceiver);
	loader.registerTypeClassReceiver(tclassReceiver);
	loader.registerTypeClassInfoReceiver(tinfoReceiver);

	loader.loadTypeClass("c:/code/vjmax/dlls/numbertype.dll");
	loader.loadModuleClass("c:/code/vjmax/dlls/addmodule.dll");

}

void LoadModuleTest::post() throw (std::runtime_error)
{
}
