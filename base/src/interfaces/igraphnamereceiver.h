#ifndef INCLUDED_IGRAPHNAMERECEIVER_H
#define INCLUDED_IGRAPHNAMERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IGraphNameReceiver
{
public:
 /**
  *
  */
	virtual void graphExists( const std::string& graphID, const std::string& snapID, const std::string& graphName, const std::string& snapName ) = 0;

 /**
  *
  */
	virtual void graphNoLongerExists( const std::string& graphID, const std::string& snapID ) = 0;

 /**
  *
  */
	virtual void graphRenamed( const std::string& graphID, const std::string& snapID, const std::string& newGraphName, const std::string& newSnapName ) = 0;

};
#endif
