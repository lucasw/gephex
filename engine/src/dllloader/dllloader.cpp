#include "dllloader.h"

#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#include <cassert>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "nameresolver.h"

#include "typedllloader.h"

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
#include "utils/ilogger.h"

#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"

#include "interfaces/itypeclassreceiver.h"
#include "interfaces/itypeclassinforeceiver.h"
#include "interfaces/itypeclassnamereceiver.h"



namespace dllloader
{
  extern "C" 
  {
    void moduleLog(int level, const char* sender, const char* msg);
  };

  //TODO: ugly
  static utils::AutoPtr<utils::ILogger> s_logger(0);

  void moduleLog(int level, const char* sender, const char* msg)
  {
    if (!s_logger)
      return;

    switch(level)
      {
      case 0:
	s_logger->error(sender, msg);
	break;
      case 1:
	s_logger->warning(sender, msg);
	break;
      default:
	s_logger->log(sender, msg);
      }
  }

  // Default functions
  int Dinit(void (*)(int,const char*, const char*))
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
	
  void* DgetInputAttributes(int)
  {
    return 0;
  }

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
	
  }
	
  DllLoader::DllLoader(utils::AutoPtr<utils::ILogger>& logger)
    : resolver(new NameResolver()), m_infoReceiver(0), m_classReceiver(0),
      m_specReceiver(0), m_typeInfoReceiver(0), m_typeClassReceiver(0),
	  m_logger(logger)
  {
    s_logger = logger;
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
  void DllLoader::loadModule(SharedLibraryPtr sl,
                             const std::string& moduleName)
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
	this->constructModuleClass(&fTable, sl, moduleName);
      }
    catch (std::runtime_error& e)
      {	
		m_logger->error("DllLoader::loadModule", e.what());
      }
  }
	
  void DllLoader::loadModuleClass(const std::string& moduleName)
  {		
	  try 
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
			loadModule(sl, moduleName);	
		}
		else
		{
			throw std::runtime_error("Unbekannter Dll Type.");
		}
	  }
	  catch (std::runtime_error& e)
	  {
		m_logger->error("LoadModuleClass", e.what());
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
    // und der moduleClassInfoReceiver benachrichtigt!

#if (ENGINE_VERBOSITY > 0)
    std::cout << "sync dllloader" << std::endl;
#endif
    m_infoReceiver->syncStarted();
//	m_nameReceiver->syncStarted();

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

	//m_nameReceiver->syncFinished();
    m_infoReceiver->syncFinished();
  }
	
  void DllLoader::loadTypeClass(const std::string& typeName)
  {
    // get the filename of the type
    std::map<std::string,std::string>::const_iterator it = 
      m_typ2fileName.find(typeName);
    
    if (it == m_typ2fileName.end())
      {
	throw std::runtime_error("unknown type:" + typeName);
      }

    std::string filename = it->second;

    // load the type and create class
    CTypeFunctionTable ft = loadTypeDll(filename);

    // lets get the name of the type
    utils::StructReader spec(ft.getSpec());
    std::string name = spec.getStringValue("name");

    // and the typeinfo
    int bufLen = ft.getInfo(0,0); // how big is it?
    char* data = new char[bufLen];
    int len = ft.getInfo(data,bufLen);
    // no exception thrower
	if (len == 0)
	{
		//TODO: is it ok to throw here (probably some leaks)?
	   delete[] data;
	   throw std::runtime_error("getInfo failed!");
	}
	
    utils::Buffer mi(reinterpret_cast<unsigned char*>(data), len);
    delete[] data;

    // register typename and get a unique id
    int id = resolver->registerObject(name);

    CTypeClass tc(ft, name, id);
    
    // distribute the new typeclass to the typefactory
    if ( m_typeClassReceiver != 0 )
      m_typeClassReceiver->typeClassLoaded(id, tc);

    // broadcast that there is a new type
    if ( m_typeInfoReceiver != 0 )
      m_typeInfoReceiver->typeClassLoaded(id,mi);
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
				       SharedLibraryPtr sl,
                                       const std::string& moduleName) 
  {
    if (fTable->init != 0)
      {
        if (fTable->init(moduleLog) == 0)
	  {
	    throw std::runtime_error("init of plugin " + moduleName
                                     + " failed");
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
    std::vector<std::string> inputIDs(numInputs);
		
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

	try {
	  inputIDs[i] = inputSpec.getStringValue("id");
	}
	catch (...)
	  {
	    throw std::runtime_error("id nicht angegeben");
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
    std::vector<std::string> outputIDs(numOutputs);
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
	  outputIDs[j] = outputSpec.getStringValue("id");
	}
	catch (...)
	  {
	    throw std::runtime_error("id nicht angegeben");
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
    int len = fTable->getInfo(data,bufLen);
	if (len == 0) {
		//TODO: is it ok to throw here (probably some leaks)?		
		delete[] data;
		throw std::runtime_error("getInfo failed!");
	}
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
					   CModuleClass(*fTable,attributes,name));

	m_specReceiver->moduleClassLoaded(name,ModuleClassSpec(name,inputs,
							       defaultVals,
                                                               inputIDs,
							       outputs,
                                                               outputIDs));
  
      }
    catch (...)
      {
	delete[] data;
	throw;
      }

    delete[] data;
    
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
	throw std::runtime_error("Modulname '" + name 
				 + "'doppelt bei processModFile");
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
