#ifndef INCLUDED_ITYPECLASSRECEIVER_H
#define INCLUDED_ITYPECLASSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ITypeClassReceiver
{
public:
 /**
  *
  */
	virtual void typeClassLoaded( int TypeClassID, const ITypeClass& typeClass ) = 0;

 /**
  *
  */
	virtual void typeClassUnloaded( int TypeClassID ) = 0;

};
#endif
