#ifndef INCLUDED_ISERIALIZEDGRAPHRECEIVER_H
#define INCLUDED_ISERIALIZEDGRAPHRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISerializedGraphReceiver
{
public:
 /**
  *
  */
	virtual void graphSerialized( const std::string& graphName, const std::string& serializedGraph ) = 0;

};
#endif
