#ifndef INCLUDED_IMODULECLASSINFORECEIVER_H
#define INCLUDED_IMODULECLASSINFORECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleClassInfoReceiver
{
public:
 /**
  *
  */
	virtual void moduleClassLoaded( const std::string& moduleClassName, const utils::Buffer& buf ) = 0;

 /**
  *
  */
	virtual void moduleClassUnloaded( const std::string& moduleClassID ) = 0;

 /**
  *
  */
	virtual void syncStarted(  ) = 0;

 /**
  *
  */
	virtual void syncFinished(  ) = 0;

};
#endif
