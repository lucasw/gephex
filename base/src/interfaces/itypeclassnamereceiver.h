#ifndef INCLUDED_ITYPECLASSNAMERECEIVER_H
#define INCLUDED_ITYPECLASSNAMERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ITypeClassNameReceiver
{
public:
 /**
  *
  */
	virtual void typeClassNameExists( const std::string& s ) = 0;

};
#endif
