#ifndef INCLUDED_IENGINECONTROLRECEIVER_H
#define INCLUDED_IENGINECONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IEngineControlReceiver
{
public:
  /**
   * Veranlasst die engine dazu alle Netzwerkverbindungen zu kappen.
   */
	virtual void disconnect(  ) = 0;

  /**
   * Beendet die Engine.
   */
	virtual void shutDown(  ) = 0;

};
#endif
