#ifndef INCLUDED_IRENDERERSTATUSRECEIVER_H
#define INCLUDED_IRENDERERSTATUSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IRendererStatusReceiver
{
public:
 /**
  *
  */
	virtual void started(  ) = 0;

 /**
  *
  */
	virtual void stopped(  ) = 0;

 /**
  *
  */
	virtual void renderedGraphChanged( const std::string& graphID ) = 0;

};
#endif
