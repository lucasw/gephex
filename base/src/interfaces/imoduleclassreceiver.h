#ifndef INCLUDED_IMODULECLASSRECEIVER_H
#define INCLUDED_IMODULECLASSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleClassReceiver
{
public:
 /**
  *
  */
	virtual void moduleClassLoaded( const std::string& moduleClassID, const IModuleClass& moduleClass ) = 0;

 /**
  *
  */
	virtual void moduleClassUnloaded( const std::string& moduleClassID ) = 0;

};
#endif
