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

#include "dllloader.h"

#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#include <cassert>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <list>

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
#include "utils/filesystem.h"
#include "utils/stringtokenizer.h"



#include "interfaces/imoduleclassreceiver.h"
#include "interfaces/imoduleclassspecreceiver.h"
#include "interfaces/imoduleclassinforeceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"

#include "interfaces/itypeclassreceiver.h"
#include "interfaces/itypeclassinforeceiver.h"

#include "frei0rwrapper.h"

namespace dllloader
{
  extern "C" 
  {
    void moduleLog(int level, const char* sender, const char* msg);
  };

  void readFrei0rFuns(DllLoader::SharedLibraryPtr sl, frei0r_funs_t& f0r)
  {
    f0r.init            = (f0r_init_t) sl->loadSymbol("f0r_init");
    f0r.deinit          = (f0r_deinit_t) sl->loadSymbol("f0r_deinit");
    f0r.get_plugin_info = (f0r_get_plugin_info_t) 
      sl->loadSymbol("f0r_get_plugin_info");
    f0r.get_param_info  = (f0r_get_param_info_t)
      sl->loadSymbol("f0r_get_param_info");
    f0r.construct       = (f0r_construct_t) sl->loadSymbol("f0r_construct");
    f0r.destruct        = (f0r_destruct_t) sl->loadSymbol("f0r_destruct");
    f0r.set_param_value = (f0r_set_param_value_t) sl->loadSymbol("f0r_set_param_value");
    f0r.get_param_value = (f0r_get_param_value_t)
      sl->loadSymbol("f0r_get_param_value");
    f0r.update          = (f0r_update_t) sl->loadSymbol("f0r_update");
	  
    if (f0r.init == 0 || f0r.deinit == 0 || f0r.get_plugin_info == 0 ||
	f0r.get_param_info == 0 || f0r.construct == 0 || f0r.destruct == 0 ||
	f0r.set_param_value == 0 || f0r.get_param_value == 0 ||
	f0r.update == 0)
      {
	throw std::runtime_error("Funkti0rs are missing!");
      }
  }

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
    void postLoadModule(CModuleFunctionTable& ft, bool is_frei0r)
    {
      if (ft.newInstance == 0 || ft.deleteInstance == 0 ||
	  ft.update == 0 ||
	  (!is_frei0r && ft.getSpec == 0) ||
	  (!is_frei0r && ft.getInfo == 0)) //TODO
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

  #if defined(OS_WIN32)
  static const char* MODULE_ENDING = ".dll";
  static const char* TYPE_ENDING   = ".dll";
#elif defined(OS_POSIX)
  static const char* MODULE_ENDING = ".so";
  static const char* TYPE_ENDING   = ".so";
#else
#error "unknown OS"
#endif

  std::vector<std::string> getFilesInPath(const std::string& dirName,
                                          const std::string& ending)
  {
    std::vector<std::string> fileNames;
    
    std::list<utils::DirEntry> entries;
    utils::FileSystem::listDir(dirName, entries);
    
    for (std::list<utils::DirEntry>::const_iterator it = entries.begin();
         it != entries.end(); ++it)
      {
        std::string name = it->getName();

        if (name == "." || name == "..")
          continue;
      
        if (it->getType() == utils::DirEntry::DIRECTORY)
          {
            std::vector<std::string> 
              subfiles= getFilesInPath(name, ending);

            fileNames.insert(fileNames.end(),
                             subfiles.begin(), subfiles.end());
          }
        else
          {
            if (name.length() > ending.length() 
                && name.substr(name.length()-ending.length(),
                               ending.length()) == ending)
              {
                fileNames.push_back(dirName + name);
              }
          }
      }
    return fileNames;
  }

  /**
   * Returns a vector of all files in a list of paths, that have a certain
   * file ending.
   * Files can be listed more than once if a path of the list is a subpath
   * of another path in the list.
   */
  std::vector<std::string> getFilesInPathList(const std::string& pathList,
					      const std::string& ending)
  {
    std::vector<std::string> files;

    utils::StringTokenizer st(pathList);
    std::string path;

    while ((path = st.next(";")) != "")
    try
      {
        std::vector<std::string> fs = getFilesInPath(path, ending);
        files.insert(files.end(),fs.begin(), fs.end());
      }
    catch (...)
      {
        // we ignore all paths we cannot open
      }

    return files;
  }

	
  DllLoader::DllLoader(utils::AutoPtr<utils::ILogger>& logger,
		       IModuleClassInfoReceiver& infoReceiver,
		       IModuleClassSpecReceiver& specReceiver,
		       IModuleClassReceiver& classReceiver,
		       //		       ITypeClassInfoReceiver& typeInfoReceiver,
		       ITypeClassReceiver& typeClassReceiver,
		       const std::string& module_path,
		       const std::string& type_path,
		       const std::string& frei0r_path
		       )
    : resolver(new NameResolver()),
      m_infoReceiver(infoReceiver),
      m_classReceiver(classReceiver),
      m_specReceiver(specReceiver),
      //      m_typeInfoReceiver(typeInfoReceiver),
      m_typeClassReceiver(typeClassReceiver), m_logger(logger)
  {
    s_logger = logger;

    // load stuff
    std::vector<std::string> modules = getFilesInPathList(module_path,
                                                          MODULE_ENDING);
	
    std::vector<std::string> types = getFilesInPathList(type_path,
                                                        TYPE_ENDING);

    std::vector<std::string> frei0rs;
    if (frei0r_path != "")
      frei0rs = getFilesInPathList(frei0r_path, MODULE_ENDING);
    
    std::cout << "Reading plugins...";
    std::cout.flush();
    readDlls(modules, types, frei0rs);
    std::cout << "   done\n";
  }
	
  DllLoader::~DllLoader()
  {
    // TODO
    //
    // 1. call cleanup/deinit methods of all types/effects/plugins
    // 2. release shared library
    
    delete resolver;
  }

  void DllLoader::readDlls(const std::vector<std::string>& modules,
			   const std::vector<std::string>& types,
			   const std::vector<std::string>& frei0rs)
  {
    for (std::vector<std::string>::const_iterator it = types.begin();
	 it != types.end(); ++it)
      {
	try 
	  {
#if (ENGINE_VERBOSITY > 0)
	    std::cout << "processing typ file: " << *it << std::endl;
#endif
	    processTypeFile(*it);
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

    for (std::vector<std::string>::const_iterator it = frei0rs.begin();
	 it != frei0rs.end(); ++it)
      {	
	try 
	  {
	    processFrei0rFile(*it);
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
	postLoadModule(fTable, false);
	this->constructModuleClass(&fTable, sl, moduleName, 0);
      }
    catch (std::runtime_error& e)
      {	
		m_logger->error("DllLoader::loadModule", e.what());
      }
  }

  void DllLoader::loadFrei0r(frei0r_funs_t& f0r, SharedLibraryPtr sl,
			     const std::string moduleName)
  {
    CModuleFunctionTable fTable;

    create_f0r_wrapper(fTable);
	
    try
      {
	postLoadModule(fTable, true);
	this->constructModuleClass(&fTable, sl, moduleName, &f0r);
      }
    catch (std::runtime_error& e)
      {	
	m_logger->error("DllLoader::loadModule", e.what());
      }
  }
	
	
  void DllLoader::synchronize()
  {
    //TODO: bis jetzt wird nur moduleClassInfoReceiver benachrichtigt!

#if (ENGINE_VERBOSITY > 0)
    std::cout << "sync dllloader" << std::endl;
#endif
    m_infoReceiver.syncStarted();

    for (std::map<std::string,utils::AutoPtr<utils::Buffer> >::const_iterator
	   modIt = m_moduleInfos.begin();
	 modIt != m_moduleInfos.end(); ++modIt)
      {
	m_infoReceiver.moduleClassLoaded(modIt->first, *modIt->second);
      }

    m_infoReceiver.syncFinished();
  }
	
  void DllLoader::processTypeFile(const std::string& filename)
  {
    std::string typeName = getDllName(filename);

    std::map<std::string,std::string>::const_iterator 
      it = m_typ2fileName.find(typeName);

    if (it != m_typ2fileName.end())
      {
	throw std::runtime_error("typname '" + typeName +"' doppelt bei processtypFile");
      }

    m_typ2fileName[typeName] = filename;

    // load the type and create class
    std::pair<CTypeFunctionTable,utils::AutoPtr<utils::SharedLibrary> > p
      = loadTypeDll(filename);

    CTypeFunctionTable ft= p.first;

	
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
    m_typeClassReceiver.typeClassLoaded(id, tc);
  }
	
  void DllLoader::constructModuleClass(CModuleFunctionTable* fTable,
				       SharedLibraryPtr sl,
                                       const std::string& moduleName,
				       frei0r_funs_t* frei0r)
  {
    int frei0r_plugin_type = -1;

    if (frei0r)
      {
	if (frei0r->init() == 0)
	  {
	    throw std::runtime_error("init0r of plugin " + moduleName
				     + " failed");
	  }
      }
    else
      {
	if (fTable->init != 0)
	  {
	    if (fTable->init(moduleLog) == 0)
	      {
		throw std::runtime_error("init of plugin " + moduleName
					 + " failed");
	      }
	  }
      }

    int numInputs;
    int numOutputs ;
    std::string moduleSpec;
    bool isDeterministic;
    f0r_plugin_info_t f0r_info;
    if (frei0r)
      {
	frei0r->get_plugin_info(&f0r_info);

        frei0r_check_plugin_info(f0r_info);

        // remember this for later
        frei0r_plugin_type = f0r_info.plugin_type;

        numInputs = frei0r_num_inputs(f0r_info);

	numOutputs = 1;
	isDeterministic = false;

	moduleSpec = frei0r_create_spec(f0r_info);
      }
    else
      {
	moduleSpec = fTable->getSpec();
      }

    utils::StructReader spec(moduleSpec);

    try {
      numInputs = spec.getIntValue("number_of_inputs");
    }
    catch (...)
      {
	throw std::runtime_error("number_of_inputs nicht angegeben");
      }
    try
      {
	numOutputs = spec.getIntValue("number_of_outputs");
      }
    catch (...)
      {
	throw std::runtime_error("number_of_outputs nicht angegeben");
      }
    
    isDeterministic = spec.getBoolValue("deterministic", false);

  std::vector<int> inputs(numInputs);
  std::vector<utils::Buffer> 
  defaultVals(numInputs,
	      utils::Buffer(reinterpret_cast<const unsigned char*>(""),1));
  std::vector<std::string> inputNames(numInputs);
  std::vector<std::string> inputIDs(numInputs);
		
  std::vector<bool> isConst(numInputs);
  std::vector<bool> isStrong(numInputs);
  std::vector<const TypeAttributes*> fixedAttributes(numInputs);

  std::vector<f0r_param_info_t> f0r_param_infos;

  for (int i = 0; i < numInputs; ++i)
      {
	std::string inSpec;
	if (frei0r)
	  {
            std::string param_name;
            inSpec = frei0r_create_in_param_spec(f0r_info, frei0r, i,
                                                 f0r_param_infos);
#if (ENGINE_VERBOSITY > 1)
            std::cout << "param # " << i << ": '" << inSpec << "'\n";
#endif
          }
	else
	  {
	    inSpec = fTable->getInputSpec(i);
	  }

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
	std::string outSpec;
	if (frei0r)
	  {
	    outSpec = frei0r_create_out_spec();
	  }
	else
	  {
	    outSpec = fTable->getOutputSpec(j);
	  }
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

    char* data = 0;
    int bufLen = 0;
    if (frei0r)
      {
	std::vector<char> buf = frei0r_create_info(f0r_info,
						   f0r_param_infos);

#if (ENGINE_VERBOSITY > 1)
        std::cout << "Inf0r: '" << &buf[0] << "'\n";
#endif
	data = new char[buf.size()];
	memcpy(data, &buf[0], buf.size());
	bufLen = buf.size();
      }
    else
      {
	bufLen = fTable->getInfo(0,0);
	data = new char[bufLen];
	int len = fTable->getInfo(data,bufLen);
	if (len == 0) {
	  //TODO: is it ok to throw here (probably some leaks)?		
	  delete[] data;
	  throw std::runtime_error("getInfo failed!");
	}
      }
    try 
      {
	utils::Buffer mi = 
	  ModuleInfo::enrichInfo(data, bufLen, name, inputNames, outputNames);

	//int id = resolver->registerObject(name);
	m_moduleInfos[name] 
	  = utils::AutoPtr<utils::Buffer>(new utils::Buffer(mi));
		
	m_moduleHandles[name] = sl;
			
	m_infoReceiver.moduleClassLoaded(name,mi);

        CModuleClass cm(*fTable,attributes,name, frei0r, frei0r_plugin_type);
	m_classReceiver.moduleClassLoaded(name, cm);

	m_specReceiver.moduleClassLoaded(name,ModuleClassSpec(name,inputs,
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
	throw std::runtime_error("A module with id '" + name 
				 + "' already exists in plugin " + it->second);
      }

    m_mod2fileName[name] = fname;

    // and load it
    try 
      {
	SharedLibraryPtr sl = this->loadDll(fname);
	if (sl->loadSymbol("update") != 0)
	  {
	    loadModule(sl, name);	
	  }
	else
	  {
	    throw std::runtime_error("Unknown Dll Type.");
	  }
      }
    catch (std::runtime_error& e)
      {
	m_logger->error("LoadModuleClass", e.what());
      }
  }



  void DllLoader::processFrei0rFile(const std::string& fname)
  {
    frei0r_funs_t f0r;
    SharedLibraryPtr sl = loadDll(fname);
    readFrei0rFuns(sl, f0r);

    if (!f0r.init())
      throw std::runtime_error("init0r failed");

    f0r_plugin_info_t inf0r;
    f0r.get_plugin_info(&inf0r);
    std::string name = std::string("mod_") + inf0r.name;

#if (ENGINE_VERBOSITY > 1)
    std::cout << "Nam0r = " << name << "\n";
#endif

    f0r.deinit();

    std::map<std::string,std::string>::const_iterator 
      it = m_f0r2fileName.find(name);

    if (it != m_f0r2fileName.end())
      {
	throw std::runtime_error("Nam0r '" + name 
				 + "'doppelt bei processFrei0rFile");
      }

    m_f0r2fileName[name] = fname;

    // and load it
    try 
      {
	frei0r_funs_t f0r;
	SharedLibraryPtr sl = this->loadDll(fname);
	
	readFrei0rFuns(sl, f0r);
	
	loadFrei0r(f0r, sl, name);
      }
    catch (std::runtime_error& e)
      {
	m_logger->error("LoadModuleClass", e.what());
      }
  }

  


}
