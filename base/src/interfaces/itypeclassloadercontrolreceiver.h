#ifndef INCLUDED_ITYPECLASSLOADERCONTROLRECEIVER_H
#define INCLUDED_ITYPECLASSLOADERCONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ITypeClassLoaderControlReceiver
{
public:
 /**
  *
  */
	virtual void loadTypeClass( const std::string& name ) = 0;

 /**
  *
  */
	virtual void unloadTypeClass( const std::string& name ) = 0;

};
#endif
