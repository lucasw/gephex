#ifndef INCLUDED_IMODULECLASSLOADERCONTROLRECEIVER_H
#define INCLUDED_IMODULECLASSLOADERCONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleClassLoaderControlReceiver
{
public:
  /**
   *
   */
	virtual void loadModuleClass( const std::string& name ) = 0;

  /**
   *
   */
	virtual void unloadModuleClass( const std::string& name ) = 0;

  /**
   * Veranlasst das Model dazu alle Receiver zu synchronisieren.
   * Dazu wird zuerst syncStarted() der Receiver aufgerufen.
   * Dann werden den Receivern über moduleClassLoaded,...
   * Aufrufe alle ModuleClassen mitgeteilt.
   * Beendet wird die Synchronisation mit syncFinished().
   */
	virtual void synchronize(  ) = 0;

};
#endif
