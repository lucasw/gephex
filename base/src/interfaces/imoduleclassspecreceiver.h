#ifndef INCLUDED_IMODULECLASSSPECRECEIVER_H
#define INCLUDED_IMODULECLASSSPECRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleClassSpecReceiver
{
public:
 /**
  *
  */
	virtual void moduleClassLoaded( const std::string& moduleClassID, const IModuleClassSpec& spec ) = 0;

 /**
  *
  */
	virtual void moduleClassUnloaded( const std::string& moduleClassID ) = 0;

};
#endif
