#ifndef INCLUDED_ITYPECLASSINFORECEIVER_H
#define INCLUDED_ITYPECLASSINFORECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ITypeClassInfoReceiver
{
public:
/**
*
*/
	virtual void typeClassLoaded( int TypeClassID, const utils::Buffer& buf ) = 0;

/**
*
*/
	virtual void typeClassUnloaded( int TypeClassID ) = 0;

};
#endif
