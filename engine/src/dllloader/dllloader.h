#ifndef INCLUDED_DLLLOADER_H
#define INCLUDED_DLLLOADER_H

#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "interfaces/imoduleclassloadercontrolreceiver.h"
#include "interfaces/imoduleclassinfosender.h"
#include "interfaces/imoduleclasssender.h"
#include "interfaces/imoduleclassspecsender.h"
#include "interfaces/imoduleclassnamesender.h"

#include "interfaces/itypeclassloadercontrolreceiver.h"
#include "interfaces/itypeclassinfosender.h"
#include "interfaces/itypeclasssender.h"
#include "interfaces/itypeclassnamesender.h"

#include "utils/autoptr.h"

namespace utils {
  class Buffer;
  class SharedLibrary;
}


class NameResolver;
class CTypeFunctionTable;
class CModuleFunctionTable;

namespace dllloader
{

/**
 * Die Klasse Dllloader kuemmert sich um das dynamische Nachladen
 * von Typ und Modul dlls.
 */
class DllLoader: 
	public IModuleClassLoaderControlReceiver,
	public ITypeClassLoaderControlReceiver,
	public IModuleClassInfoSender, 
	public IModuleClassSpecSender, 
	public IModuleClassSender, 
	public ITypeClassInfoSender, 
	public ITypeClassSender,
	public IModuleClassNameSender,
	public ITypeClassNameSender
{

public:
  /**
   * Erzeugt neuen DllLoader.
   * @param mc Der ModuleConstructor mit dem ein geladenes Modul
   *           in die engine integriert wird.
   */
  DllLoader();

  virtual ~DllLoader();

  /**
   * Liest und verarbeitet die module und die typ dateien.
   * Davor sollte der ModuleClassNameReceiver registriert sein !!
   */
  void readDlls(const std::vector<std::string>& modules,
		const std::vector<std::string>& types);

  virtual void loadModuleClass(const std::string& name);
  virtual void unloadModuleClass(const std::string& name);

    //TODO: war mal const
  virtual void synchronize();

  /**
   * Unloads all module and type dlls. Should be called before
   * the listeners are destroyed.
   */
  void unloadAll();
  
  virtual void registerModuleClassInfoReceiver(IModuleClassInfoReceiver&);
  virtual void registerModuleClassSpecReceiver(IModuleClassSpecReceiver&);
  virtual void registerModuleClassReceiver(IModuleClassReceiver&);
  virtual void registerModuleClassNameReceiver(IModuleClassNameReceiver&);

  virtual void loadTypeClass(const std::string& name);
  virtual void unloadTypeClass(const std::string& name);
  virtual void registerTypeClassInfoReceiver(ITypeClassInfoReceiver&);
  virtual void registerTypeClassReceiver(ITypeClassReceiver&);
  virtual void registerTypeClassNameReceiver(ITypeClassNameReceiver&);

private:
  typedef utils::AutoPtr<utils::SharedLibrary> SharedLibraryPtr;

	SharedLibraryPtr loadDll(const std::string& filename);
	std::string getDllName(const std::string& filename);

	void loadModule(SharedLibraryPtr);
	void loadType(SharedLibraryPtr);

	void processModFile(const std::string&);
	void processTypFile(const std::string&);
	
	void constructModuleClass(CModuleFunctionTable* fTable,
				  SharedLibraryPtr sl);

	void constructTypeClass(CTypeFunctionTable* fTable,
				SharedLibraryPtr sl);

	NameResolver* resolver;

	IModuleClassInfoReceiver* m_infoReceiver;
	IModuleClassReceiver* m_classReceiver;
	IModuleClassSpecReceiver* m_specReceiver;
	IModuleClassNameReceiver* m_nameReceiver;

	ITypeClassInfoReceiver* m_typeInfoReceiver;
	ITypeClassReceiver* m_typeClassReceiver;
	ITypeClassNameReceiver* m_typeNameReceiver;

	std::map<std::string,std::string> m_mod2fileName;
	std::map<std::string,std::string> m_typ2fileName;
	std::map<std::string,SharedLibraryPtr> m_moduleHandles;
	std::map<std::string,utils::AutoPtr<utils::Buffer> > m_moduleInfos;
	std::map<std::string,SharedLibraryPtr> m_typeHandles;
};

}

#endif
