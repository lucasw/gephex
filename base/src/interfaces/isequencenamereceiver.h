#ifndef INCLUDED_ISEQUENCENAMERECEIVER_H
#define INCLUDED_ISEQUENCENAMERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISequenceNameReceiver
{
public:
 /**
  *
  */
	virtual void sequenceExists( const std::string& id, const std::string& name ) = 0;

 /**
  *
  */
	virtual void sequenceNoLongerExists( const std::string& id ) = 0;

 /**
  *
  */
	virtual void sequenceRenamed( const std::string& id, const std::string& newName ) = 0;

};
#endif
