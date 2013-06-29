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

#ifdef WIN32
#pragma warning( disable : 4786 )  
#endif 

#include "modeltest.h"
#include "model/model.h"

#include "interfaces/imodelcontrolsender.h"
#include "interfaces/imoduleconstructionsmartreceiver.h"
#include "interfaces/imoduleconstructiondumbreceiver.h"
#include "interfaces/imoduleclassspecsender.h"
#include "interfaces/igraphnamereceiver.h"
#include "dllloader/moduleclassspec.h"

#include <vector>
#include <iostream>

class DummyModelControlSender: public IModelControlSender
{
private:
	IModelControlReceiver* mcr;
public:
	DummyModelControlSender() {}
	virtual void registerModelControlReceiver(IModelControlReceiver&);
	//bah..und da das ganze add und delete zeugs und so..uhm..TODO
};

void DummyModelControlSender::registerModelControlReceiver(IModelControlReceiver& _mcr)
{
	mcr = &_mcr;
}

class DummyModuleConstructionSmartReceiver : public IModuleConstructionSmartReceiver
{
public:
	DummyModuleConstructionSmartReceiver() {}
	virtual void moduleAdded(int graphID, int moduleClassID,int modID);
	
	
	virtual void modulesConnected(int graphID, int moduleID1,int outputIndex,
								int moduleID2,int inputIndex);
	virtual void modulesDisconnected(int graphID, int moduleID,int inputIndex);
	virtual void moduleDeleted(int graphID, int moduleID);
	virtual void newGraphCreated(int newGraphID);
	virtual void graphChanged(int newGraphID);
};

void DummyModuleConstructionSmartReceiver::moduleAdded(int graphID, int moduleClassID,int modID)
{
	std::cout<<"graphID: "<<graphID<<" moduleClassID: "<<moduleClassID<<" modID: "<<modID<<std::endl;
}
	
void DummyModuleConstructionSmartReceiver::modulesConnected(int graphID, int moduleID1,int outputIndex,
								int moduleID2,int inputIndex)
{
	std::cout<<"graphID: "<<graphID<<" moduleID1: "<<moduleID1<<" outputIndex: "<<outputIndex<<" moduleID2: "<<moduleID2<<" inputIndex: "<<inputIndex	<<std::endl;	
								
}

void DummyModuleConstructionSmartReceiver::modulesDisconnected(int graphID, int moduleID,int inputIndex)
{
	std::cout<<" graphID: " << graphID << " moduleID: " << moduleID << " inputIndex: " << inputIndex <<std::endl;
}

void DummyModuleConstructionSmartReceiver::moduleDeleted(int graphID, int moduleID)
{
	std::cout<< " graphID: " << graphID << " moduleID: " << moduleID << std::endl;
}

void DummyModuleConstructionSmartReceiver::newGraphCreated(int newGraphID)
{
	std::cout<<" newGraphID: " << newGraphID << std::endl;
}

void DummyModuleConstructionSmartReceiver::graphChanged(int newGraphID)
{
	std::cout<<" newGraphID: " << newGraphID << std::endl;
}



class DummyModuleConstructionDumbReceiver : public IModuleConstructionDumbReceiver
{
public:
	DummyModuleConstructionDumbReceiver(){}
	virtual void moduleAdded(int moduleClassID,int modID);
	virtual void modulesConnected(int moduleID1,int outputIndex,
								int moduleID2,int inputIndex);
	virtual void modulesDisconnected( int moduleID,int inputIndex);
	virtual void moduleDeleted(int moduleID);
	virtual void graphChanged(const std::string& name);
//	virtual void moduleDataSet(const Buffer&);
};

void DummyModuleConstructionDumbReceiver::moduleAdded(int moduleClassID,int modID)
{
	std::cout<<"moduleClassID: "<<moduleClassID<<" modID: "<<modID<<std::endl;
}

void DummyModuleConstructionDumbReceiver::modulesConnected(int moduleID1,int outputIndex,
								int moduleID2,int inputIndex)
{
	std::cout<<"moduleID1: "<<moduleID1<<" outputIndex: "<<outputIndex<<" moduleID2: "<<moduleID2<<" inputIndex: "<<inputIndex	<<std::endl;		
}
								
void DummyModuleConstructionDumbReceiver::modulesDisconnected( int moduleID,int inputIndex)
{
	std::cout<< "moduleID: " << moduleID << " inputIndex: " << inputIndex <<std::endl;
}

void DummyModuleConstructionDumbReceiver::moduleDeleted(int moduleID)
{
	std::cout<< "moduleID: " << moduleID << std::endl;
}

void DummyModuleConstructionDumbReceiver::graphChanged(const std::string& name)
{
	std::cout<< "graphName: " << name << std::endl;
}

/*void DummyModuleConstructionDumbReceiver::moduleDataSet(const Buffer&)
{
	std::cout << "no net da...\n";
}*/

class DummyModuleClassSpecSender : public IModuleClassSpecSender
{
	IModuleClassSpecReceiver *mcsp;
public:
	DummyModuleClassSpecSender():mcsp(0) {}
	virtual void registerModuleClassSpecReceiver(IModuleClassSpecReceiver&);
	void loadModuleClass();
};

void DummyModuleClassSpecSender::loadModuleClass()
{
	// TODO: uhm...this eventually makes no sense at all...
	std::vector<int> ins(4);
	std::vector<int> outs(2);

	ins[0] = 1;
	ins[1] = 1;
	ins[2] = 1;
	ins[3] = 1;
	outs[0] = 1;
	outs[1] = 1;

	ModuleClassSpec spec("0",ins, outs);
	ModuleClassSpec spec2("1",ins, outs);

	mcsp->moduleClassLoaded("0", spec);
	mcsp->moduleClassLoaded("1", spec2);
}

void DummyModuleClassSpecSender::registerModuleClassSpecReceiver(IModuleClassSpecReceiver& _mcsp)
{
	mcsp = &_mcsp;
}

class DummyGraphNameReceiver :public IGraphNameReceiver
{
public:
	DummyGraphNameReceiver() {}
	virtual void graphExists(const std::string& name);
	
};

void DummyGraphNameReceiver::graphExists(const std::string& name)
{
	if(name != "TestGraph1")
		throw std::runtime_error("Name ist nicht TestGraph1 bei graphExists!!");

}


ModelTest::ModelTest():  EasyTest("ModelTest","")
{}

ModelTest::~ModelTest()
{}

void ModelTest::pre() 
{}

void ModelTest::run() 
{
	IModelControlSender* dmcr = new DummyModelControlSender();
	IModuleConstructionSmartReceiver* dmcsr = new DummyModuleConstructionSmartReceiver();
	IModuleConstructionDumbReceiver* dmcdr = new DummyModuleConstructionDumbReceiver();
	IGraphNameReceiver* dgnr= new DummyGraphNameReceiver();
	DummyModuleClassSpecSender* dcss= new DummyModuleClassSpecSender();

	model::Model* testModel = new model::Model();


	dmcr->registerModelControlReceiver(*testModel);
	dcss->registerModuleClassSpecReceiver(*testModel);

	testModel->registerModuleConstructionSmartReceiver(*dmcsr);
	testModel->registerModuleConstructionDumbReceiver(*dmcdr);
	testModel->registerGraphNameReceiver(*dgnr);

	testModel->newGraph("TestGraph1");
	dcss->loadModuleClass();
	testModel->changeGraph("TestGraph1");
	
	std::cout<< "adding module, soll= 0\n";
	testModel->addModule(0) ;
	std::cout<< "adding module, soll= 1\n";
	testModel->addModule(1) ;
	
	
	std::cout<< "connecting modules: soll: modID1: 0, outputIndex: 1, modID2: 1, inputIndex: 2\n";
	testModel->connectModules(0,1,1,2);
	std::cout<< "connecting modules: soll: Fehler!\n";
	try
	{
		testModel->connectModules(0,1,1,10);
	}
	catch(std::runtime_error e)
	{
		std::cout<<e.what()<<std::endl;
	}
	
	std::cout<< "disconnecting modules: soll: modID: 1, inputIndex: 2\n";
	testModel->disconnectModules(1, 2) ;
	std::cout<< "disconnecting modules: soll: Fehler!\n";
	try
	{
		testModel->disconnectModules(1, 2) ;
	} 
	catch(std::runtime_error e)
	{
		std::cout<<e.what()<<std::endl;
	}
	std::cout<<"deleting modules: soll: modID 1\n";
	testModel->deleteModule(1);
	std::cout<<"deleting modules: soll: Fehler!\n";
	try
	{
		testModel->deleteModule(3);
	}
	catch(std::runtime_error e)
	{
		std::cout<<e.what()<<std::endl;
	}
		//testModule->setModuleData(int moduleID,const Buffer& buf);

	
	//testModule->changeGraph(const std::string& name);
	//testModule->newGraph(const std::string& name);

}

void ModelTest::post()
{}
