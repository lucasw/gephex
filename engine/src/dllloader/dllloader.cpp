#include "dllloader.h"

#include <cassert>
#include <string>
#include <sstream>

#include "config.h"

#include <stdexcept>

#include <iostream>

#include "nameresolver.h"

#include "c_moduletables.h"
#include "c_typetables.h"
#include "c_typeclass.h"
#include "c_moduleclass.h"

#include "moduleinfoutils.h" 
#include "moduleclassspec.h" 

#include "utils/structreader.h"
#include "utils/buffer.h"
#include "utils/autoptr.h"
#include "utils/sharedlibrary.h"

#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"

#include "interfaces/itypeclassreceiver.h"
#include "interfaces/itypeclassinforeceiver.h"
#include "interfaces/itypeclassnamereceiver.h"


namespace dllloader
{	
  // Default functions
  int Dinit(void (*)(int,const char*))
  {
    return 1;
  }
	
  void DshutDown()
  {
  }
	
  void DparseInput(void*,const char*,int)
  {
    throw std::runtime_error("Operation parseInput() not supported by this"
			     "module!");
  }
	
	
  int DattributesEqual(void*,void*)
  {
    /*throw std::runtime_error("Operation attributesEqual() not "
      "supported by this module!");*/

    return 1;
  }

  void DconvertType(void*,void*,void*)
  {
    throw std::runtime_error("Operation convertType() not supported by this "
			     "type!");
  }

  void* DgetInputAttributes(int)
  {
    return 0;
  }

  /*  void DgetPatchLayout(void* instance, int** out2in)
  {
	*out2in=0;
	}*/

  namespace
  {
    void postLoadModule(CModuleFunctionTable& ft)
    {
      if (ft.newInstance == 0 || ft.deleteInstance == 0
	  || ft.update == 0 || ft.getSpec == 0 || ft.getInfo == 0) //TODO
	throw std::runtime_error("Benoetigte Funktion fehlt");
		
      if (ft.init == 0)
	ft.init = Dinit;
		
      if (ft.shutDown == 0)
	ft.shutDown = DshutDown;
		
      if (ft.parseInput == 0)
	ft.parseInput = DparseInput;
	
	  
      if (ft.getInputAttributes == 0)
	ft.getInputAttributes = DgetInputAttributes;
      // TODO: Konsistenz testen

      //	  if (ft.getPatchLayout == 0)
      //		ft.getPatchLayout = DgetPatchLayout;

    }
	
    void postLoadType(CTypeFunctionTable& ft)
    {
      if (ft.newInstance == 0 || ft.deleteInstance == 0
	  || ft.getSpec == 0 || ft.getInfo == 0) //TODO
	throw std::runtime_error("Benoetigte Funktion fehlt");
		
      if (ft.init == 0)
	ft.init = Dinit;
		
      if (ft.shutDown == 0)
	ft.shutDown = DshutDown;
		

      if(ft.attributesEqual == 0)
	ft.attributesEqual = DattributesEqual;

      if(ft.convertType == 0)
	ft.convertType = DconvertType;
      // TODO: Konsistenz testen
    }
  }
	
  DllLoader::DllLoader()
    : resolver(new NameResolver()), m_infoReceiver(0), m_classReceiver(0),
      m_specReceiver(0), m_typeInfoReceiver(0), m_typeClassReceiver(0)
  {
  }
	
  DllLoader::~DllLoader()
  {
    delete resolver;
  }

  void DllLoader::unloadAll()
  {
    //unload all loaded modules
    typedef std::vector<std::pair<std::string, void*> > Fotze;
    Fotze names(m_moduleHandles.size());

    std::copy(m_moduleHandles.begin(), m_moduleHandles.end(),
	      names.begin());	
    
    for (Fotze::const_iterator it = names.begin() ;it != names.end(); ++it)
      {
	std::string name = it->first;
#if (ENGINE_VERBOSITY > 1)
	std::cout << "Unloading " << name << std::endl;
#endif
	unloadModuleClass(name);
      }
    //TODO: unload type classes
  }

  void DllLoader::readDlls(const std::vector<std::string>& modules,
			   const std::vector<std::string>& types)
  {
    for (std::vector<std::string>::const_iterator it = types.begin();
	 it != types.end(); ++it)
      {
	try 
	  {
#if (ENGINE_VERBOSITY > 0)
	    std::cout << "processing typ file: " << *it << std::endl;
#endif
	    processTypFile(*it);
	  }
	catch (std::runtime_error& e)
	  {
	    std::cerr << e.what() << std::endl;
	  }
      }
		
    for (std::vector<std::string>::const_iterator it = modules.begin();
	 it != modules.end(); ++it)
      {	
	try 
	  {
	    processModFile(*it);
	  }
	catch (std::runtime_error& e)
	  {
	    std::cerr << e.what() << std::endl;
	  }
      }		
  }
	
  //TODO: Fehlerbehandlung!
  void DllLoader::loadModule(SharedLibraryPtr sl)
  {
    CModuleFunctionTable fTable;
		
    fTable.init = (initT) sl->loadSymbol("initSO");
		
    fTable.shutDown = (shutDownT) sl->loadSymbol("shutDown");
		
    fTable.newInstance = (newInstanceT) sl->loadSymbol("newInstance");
		
    fTable.deleteInstance = (deleteInstanceT) sl->loadSymbol("deleteInstance");
		
    fTable.getSpec = (getSpecT) sl->loadSymbol("getSpec");
		
    fTable.getOutputSpec = (getOutputSpecT) sl->loadSymbol("getOutputSpec");
		
    fTable.getInputSpec = (getInputSpecT) sl->loadSymbol("getInputSpec");
		
    fTable.getInfo = (getInfoT) sl->loadSymbol("getInfo");
		
    fTable.setOutput = (setOutputT) sl->loadSymbol("setOutput");
		
    fTable.setInput = (setInputT) sl->loadSymbol("setInput");
		
    fTable.update = (updateT) sl->loadSymbol("update");
		
    fTable.parseInput = (parseInputT) sl->loadSymbol("parseInput");
		
    fTable.strongDependenciesCalculated = (strongDependenciesCalculatedT)
      sl->loadSymbol("strongDependenciesCalculated");

    fTable.getInputAttributes = (getInputAttributesT)
      sl->loadSymbol("getInputAttributes");
	
    fTable.getPatchLayout = (getPatchLayoutT)
      sl->loadSymbol("getPatchLayout");
	
    try
      {
	postLoadModule(fTable);			
	this->constructModuleClass(&fTable, sl);
      }
    catch (std::runtime_error& e)
      {
	//TODO
	throw e;
      }
  }
	
	
  void DllLoader::loadType(SharedLibraryPtr sl)
  {
    CTypeFunctionTable* fTable = new CTypeFunctionTable(); //TODO: memory leak
		
    fTable->newInstance = (newInstanceT) sl->loadSymbol("newInstance");
		
    fTable->deleteInstance = (deleteInstanceT) sl->loadSymbol("deleteInstance");
		
    fTable->init = (initT) sl->loadSymbol("init");
		
    fTable->shutDown = (shutDownT) sl->loadSymbol("shutDown");
		
    fTable->getSpec = (getSpecT) sl->loadSymbol("getSpec");
    fTable->getInfo = (getInfoT) sl->loadSymbol("getInfo");
		
    fTable->assign = (assignT) sl->loadSymbol("assign");
		
    fTable->serialize = (serializeT) sl->loadSymbol("serialize");
		
    fTable->deSerialize = (deSerializeT) sl->loadSymbol("deSerialize");

    fTable->attributesEqual = (attributesEqualT)
      sl->loadSymbol("attributesEqual");

    fTable->convertType = (convertTypeT) sl->loadSymbol("convertType");
		
    try
      {
	postLoadType(*fTable);
		
	this->constructTypeClass(fTable, sl);
      }
    catch (std::runtime_error& e)
      {
	std::cerr << "Fehler!!!!!!!!!!!!!!" << std::endl;
	throw e;
      }
  }
	
	
  void DllLoader::loadModuleClass(const std::string& moduleName)
  {		
    std::map<std::string,std::string>::const_iterator it = 
      m_mod2fileName.find(moduleName);

    if (it == m_mod2fileName.end())
      {
	throw std::runtime_error("ModulClass gibts halt nicht");
      }

    std::string filename = it->second;

    SharedLibraryPtr sl = this->loadDll(filename);
    if (sl->loadSymbol("update") != 0)
      {
	loadModule(sl);	
      }
    else
      {
	throw std::runtime_error("Unbekannter Dll Type.");
      }
  }
	
  void DllLoader::unloadModuleClass(const std::string& name)
  {
    std::map<std::string,SharedLibraryPtr>::iterator it 
      = m_moduleHandles.find(name);
    std::map<std::string,utils::AutoPtr<utils::Buffer> >::iterator 
      it2 = m_moduleInfos.find(name);

    if (it == m_moduleHandles.end() || it2 == m_moduleInfos.end())
      {
	throw std::runtime_error("unbekannte moduleclass "
				 "bei unloadmoduleclass");
      }

    m_specReceiver->moduleClassUnloaded(name);
    m_classReceiver->moduleClassUnloaded(name);
    m_infoReceiver->moduleClassUnloaded(name);

    SharedLibraryPtr sl = it->second;

    // Call the shutdown function of the dll
    shutDownT shutDown = (shutDownT) sl->loadSymbol("shutDown");

    if (shutDown != 0)
      shutDown();


    m_moduleInfos.erase(it2);
    m_moduleHandles.erase(it);
 
  }

  void DllLoader::synchronize()
  {
    //TODO: bis jetzt wird nur der moduleClassNameReceiver
    // und der moduleClassInforReceiver benachrichtigt!

#if (ENGINE_VERBOSITY > 0)
    std::cout << "sync dllloader" << std::endl;
#endif
    m_infoReceiver->syncStarted();

    for (std::map<std::string,std::string>::const_iterator nameIt 
	   = m_mod2fileName.begin();
	 nameIt != m_mod2fileName.end(); ++nameIt)
      {
	m_nameReceiver->moduleClassNameExists(nameIt->first);       
      }


    for (std::map<std::string,utils::AutoPtr<utils::Buffer> >::const_iterator
	   modIt = m_moduleInfos.begin();
	 modIt != m_moduleInfos.end(); ++modIt)
      {
	m_infoReceiver->moduleClassLoaded(modIt->first, *modIt->second);
      }

    m_infoReceiver->syncFinished();
  }
	
  void DllLoader::loadTypeClass(const std::string& typeName)
  {
    std::map<std::string,std::string>::const_iterator it = 
      m_typ2fileName.find(typeName);

    if (it == m_typ2fileName.end())
      {
	throw std::runtime_error("TypeClass '" + typeName +
				 "' gibts halt nicht");
      }

    std::string filename = it->second;

    SharedLibraryPtr sl = this->loadDll(filename);

    if (sl->loadSymbol("assign") != 0)
      {
	loadType(sl);
      }
    else
      {
	throw std::runtime_error("Unbekannter Dll Type.");
      }
  }
	
  void DllLoader::unloadTypeClass(const std::string& name)
  {
    //TODO
  }
	
  void DllLoader::registerModuleClassInfoReceiver(IModuleClassInfoReceiver& r)
  {
    m_infoReceiver = &r;
  }
	
  void DllLoader::registerModuleClassSpecReceiver(IModuleClassSpecReceiver& r)
  {
    m_specReceiver = &r;
  }
	
  void DllLoader::registerModuleClassReceiver(IModuleClassReceiver& r)
  {
    m_classReceiver = &r;
  }

  void DllLoader::registerModuleClassNameReceiver(IModuleClassNameReceiver& r)
  {
    m_nameReceiver = &r;
  }
	
  void DllLoader::registerTypeClassInfoReceiver(ITypeClassInfoReceiver& r)
  {
    m_typeInfoReceiver = &r;
  }
	
  void DllLoader::registerTypeClassReceiver(ITypeClassReceiver& r)
  {
    m_typeClassReceiver = &r;
  }

  void DllLoader::registerTypeClassNameReceiver(ITypeClassNameReceiver& r)
  {
    m_typeNameReceiver = &r;
  }
	
  void DllLoader::constructModuleClass(CModuleFunctionTable* fTable,
				       SharedLibraryPtr sl) 
  {
    if (fTable->init != 0)
      {
	if (fTable->init(0) == 0)
	  {
	    throw std::runtime_error("Initialisierung gescheitert");
	  }
      }
		
    std::string moduleSpec = fTable->getSpec();
    utils::StructReader spec(moduleSpec);
    int numInputs;
    try {
      numInputs = spec.getIntValue("number_of_inputs");
    }
    catch (...)
      {
	throw std::runtime_error("number_of_inputs nicht angegeben");
      }
		
		
    int numOutputs ;
    try
      {
	numOutputs = spec.getIntValue("number_of_outputs");
      }
    catch (...)
      {
	throw std::runtime_error("number_of_outputs nicht angegeben");
      }
		
    bool isDeterministic = spec.getBoolValue("deterministic", false);

    std::vector<int> inputs(numInputs);
    std::vector<utils::Buffer> 
      defaultVals(numInputs,
		  utils::Buffer(reinterpret_cast<const unsigned char*>(""),1));
    std::vector<std::string> inputNames(numInputs);
		
    std::vector<bool> isConst(numInputs);
    std::vector<bool> isStrong(numInputs);
    std::vector<const TypeAttributes*> fixedAttributes(numInputs);
		
    for (int i = 0; i < numInputs; ++i)
      {
	std::string inSpec = fTable->getInputSpec(i);
	utils::StructReader inputSpec(inSpec);
	
	try {
	  std::string defaultVal = inputSpec.getStringValue("default");
	  defaultVals[i] 
	    = utils::Buffer(reinterpret_cast<const unsigned char*>(defaultVal.c_str()),
			    defaultVal.length()+1);
	}
	catch(...) {}

	try {
	  inputNames[i] = inputSpec.getStringValue("type");
	}
	catch (...)
	  {
	    throw std::runtime_error("type nicht angegeben");
	  }

#if (ENGINE_VERBOSITY > 2)
	std::cout << "inputNames[" << i << "] = \"" 
		  << inputNames[i] << '"' << std::endl;
#endif
			
	try 
	  {
	    inputs[i] = resolver->getObjectID(inputNames[i]);
	  }
	catch(std::runtime_error& e)
	  {
	    std::string msg = "Unbekannter Typ: \"";
	    msg += inputNames[i];
	    msg += '"';
	    msg += " beim Laden von ";
	    msg += spec.getStringValue("name");
	    throw std::runtime_error(msg.c_str());
	  }
			
			
	try 
	  {
	    isConst[i] = (inputSpec.getBoolValue("const"));
	  }
	catch (...)
	  {
	    throw std::runtime_error("const nicht angegeben");
	  }
			
	try 
	  {
	    isStrong[i] = (inputSpec.getBoolValue("strong_dependency"));
	  }
	catch (...)
	  {
	    throw std::runtime_error("strong_dependency nicht angegeben");
	  }

	try
	  {
	    fixedAttributes[i] 
	      = static_cast<TypeAttributes*>(fTable->getInputAttributes(i));
	  }
	catch (...)
	  {
	    throw std::runtime_error("darf net sein");
	  }

      }
		
    std::vector<int> outputs(numOutputs);
    std::vector<std::string> outputNames(numOutputs);
    for (int j = 0; j < numOutputs; ++j)
      {
	std::string outSpec = fTable->getOutputSpec(j);
	utils::StructReader outputSpec(outSpec);			
			
	try {
	  outputNames[j] = outputSpec.getStringValue("type");
	}
	catch (...)
	  {
	    throw std::runtime_error("type nicht angegeben");
	  }
	try {
	  outputs[j] = resolver->getObjectID(outputNames[j]);
	}
	catch(std::runtime_error&)
	  {
	    std::string msg = "Unbekannter Typ: \"";
	    msg += outputNames[j] + '"';
	    throw std::runtime_error(msg.c_str());
	  }
      }
		
    CModuleAttributes attributes;
    attributes.inputs = inputs;
    attributes.outputs = outputs;
    attributes.isConstInput = isConst;
    attributes.isStrongDependency = isStrong;
    attributes.isDeterministic = isDeterministic;
    attributes.fixedAttributes = fixedAttributes;
		
    std::string name;
    try {
      name = spec.getStringValue("name");
    }
    catch (...)
      {
	throw std::runtime_error("name nicht angegeben");
      }

#if (ENGINE_VERBOSITY > 0)
    std::cout << "Registriere Modul " << name << std::endl;
#endif

    int bufLen = fTable->getInfo(0,0);
    char* data = new char[bufLen];
    fTable->getInfo(data,bufLen);
    try 
      {
	utils::Buffer mi = 
	  ModuleInfo::enrichInfo(data, bufLen, name, inputNames, outputNames);

	//int id = resolver->registerObject(name);
	m_moduleInfos[name] 
	  = utils::AutoPtr<utils::Buffer>(new utils::Buffer(mi));
		
	m_moduleHandles[name] = sl;
			
	m_infoReceiver->moduleClassLoaded(name,mi);

	m_classReceiver->moduleClassLoaded(name,
					   CModuleClass(*fTable,attributes));

	m_specReceiver->moduleClassLoaded(name,ModuleClassSpec(name,inputs,
							       defaultVals,
							       outputs));
  
      }
    catch (...)
      {
	delete[] data;
	throw;
      }

    delete[] data;
    
  }
  
  void DllLoader::constructTypeClass(CTypeFunctionTable* fTable,
				     SharedLibraryPtr sl)
  {
    if (fTable->init != 0)
      {
	if (fTable->init(0) == 0)
	  {
	    throw std::runtime_error("Das geht nicht!!!");
	  }
      }
	  
    std::string typeSpec = fTable->getSpec();
    utils::StructReader spec(typeSpec);
	  
    std::string name = spec.getStringValue("name");
	
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Registriere Typ: \"" << name << '"' << std::endl;
#endif	  
	  
    int bufLen = fTable->getInfo(0,0);
    char* data = new char[bufLen];
    fTable->getInfo(data,bufLen);
    utils::Buffer mi(reinterpret_cast<unsigned char*>(data),bufLen);
    delete[] data;
	  
    int id = resolver->registerObject(name);

    m_typeHandles.insert(std::make_pair(name, sl));
	  
    if (m_typeInfoReceiver != 0)
      m_typeInfoReceiver->typeClassLoaded(id,mi);
	  
    CTypeClass tc(*fTable);
    m_typeClassReceiver->typeClassLoaded(id, tc);
  }

  DllLoader::SharedLibraryPtr DllLoader::loadDll(const std::string& filename)
  {
    try {
      SharedLibraryPtr sl(new utils::SharedLibrary(filename));
#if (ENGINE_VERBOSITY > 1)
      std::cout << "Loaded Library '" << filename << "'" << std::endl;
#endif
      return sl;
    }
    catch (std::runtime_error& e) {
      std::ostringstream os;
      os << "loading plugin " << filename << " - FAIL (" 
	+ std::string(e.what()) + ")";

      std::string msg = os.str();
      std::cerr << msg << std::endl;
      throw std::runtime_error(msg.c_str());
    }
  }

  std::string DllLoader::getDllName(const std::string& fname)
  {
    utils::AutoPtr<utils::SharedLibrary> sl( loadDll(fname) );
	  
    getSpecT getSpec = (getSpecT) sl->loadSymbol("getSpec");
	  
    if (getSpec == 0)
      {
	throw std::runtime_error("Funktion getSpec fehlt!");
      }
	  
    std::string spec = getSpec();
	  
    utils::StructReader sr(spec);
	 
    std::string name;
    try {
      name = sr.getStringValue("name");
    }
    catch (...)
      {
	throw std::runtime_error("name nicht angegeben");
      }

    return name;
  }

  void DllLoader::processModFile(const std::string& fname)
  {
    std::string name = getDllName(fname);

    std::map<std::string,std::string>::const_iterator 
      it = m_mod2fileName.find(name);

    if (it != m_mod2fileName.end())
      {
	throw std::runtime_error("Modulname doppelt bei processModFile");
      }

    m_mod2fileName[name] = fname;

    m_nameReceiver->moduleClassNameExists(name);
  }

  void DllLoader::processTypFile(const std::string& fname)
  {
    std::string name = getDllName(fname);

    std::map<std::string,std::string>::const_iterator 
      it = m_typ2fileName.find(name);

    if (it != m_typ2fileName.end())
      {
	throw std::runtime_error("typname '" + name +"' doppelt bei processtypFile");
      }

    m_typ2fileName[name] = fname;

    m_typeNameReceiver->typeClassNameExists(name);
  }
  
}
