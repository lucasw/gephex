#ifndef INCLUDED_IMODULECLASSNAMERECEIVER_H
#define INCLUDED_IMODULECLASSNAMERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleClassNameReceiver
{
public:
/**
*
*/
	virtual void moduleClassNameExists( const std::string& name ) = 0;

};
#endif
