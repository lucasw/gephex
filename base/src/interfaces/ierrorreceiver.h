#ifndef INCLUDED_IERRORRECEIVER_H
#define INCLUDED_IERRORRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IErrorReceiver
{
public:
 /**
  * Is called when an error occurred.
  */
	virtual void error( const std::string& text ) = 0;

 /**
  * Is called for warnings.
  */
	virtual void warning( const std::string& text ) = 0;

 /**
  * Is called for log messages.
  */
	virtual void log( const std::string& text ) = 0;

};
#endif
