#include "xmllistenertest.h"
#include "xmllistener.h"
#include "moduleinfo.h"
#include "xpm.h"

#include <map>

XMLListenerTest::XMLListenerTest()
  : EasyTest("XMLListenerTest","")
{
}

XMLListenerTest::~XMLListenerTest()
{
}

void XMLListenerTest::pre()
{}

void XMLListenerTest::run() throw(std::runtime_error)
{
	//create a dummy map with a fakie fucking modulewhateverinfo....
	std::vector<std::pair<std::string, std::string> > outs(1);
	std::vector<std::pair<std::string, std::string> > ins(0);
	std::pair<std::string, std::string> outpair("typ_number", "Zahl");
	outs[0] = outpair;
	
	//Xpm dummy(dummyXpm, strlen(dummyXpm)+1);
	ModuleInfo* mi = new ModuleInfo("mod_intparserModule", "IntegerParser", 
								    ins, outs, true);

	
	std::vector<std::pair<std::string, std::string> > outs2(0);
	std::vector<std::pair<std::string, std::string> > ins2(1);
	std::pair<std::string, std::string> inpair("typ_framebuffer", "Bild");
	ins2[0] = inpair; 
	ModuleInfo* mi2 = new ModuleInfo("mod_glOutputModule", "GLoutput" , 
								    ins, outs, true);

	std::map<int, ModuleInfo*> mi_map;
	mi_map[0] = mi;
	mi_map[1] = mi2;	

	//create storage room for the listener
	std::map<std::string, int> infos;
	std::map<std::string, std::pair<int,int> > nodes;
	std::map<int, std::string> nodeFileIDs;
	std::map<std::string, std::pair<int,int> > controls;
	std::map<int, std::string> controlFileIDs;
	std::map<std::pair<int,int>, std::pair<int,int> > conns;
	std::map<std::pair<int,int>, std::pair<int,int> > ctrlconns;

	//create an xmlListener with that dummyinfo
	XMLTokenListener horcher(mi_map, infos, nodes, nodeFileIDs, controls, controlFileIDs, conns, ctrlconns);

	std::string node("mod_glOutputModule 333 125");
	std::string controlnode("mod_intparserModule 11 117");
	std::string connection("0 0 1 0");
	std::string connectionctrl("0 0 4 0 11 117");

	
	horcher.scannedNode(node, 0);
	horcher.scannedConnection(connection);
	horcher.scannedCtrlConnection(connectionctrl);
	horcher.scannedControlElement(controlnode, 0);

}

void XMLListenerTest::post()
{}