#ifndef INCLUDED_IGRAPHDATARECEIVER_H
#define INCLUDED_IGRAPHDATARECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IGraphDataReceiver
{
public:
   /**
   * Teilt dem Receiver mit, dass irgendwas...
   */
	virtual void graphDataSet( int type, const utils::Buffer& buf ) = 0;

   /**
   * Teilt dem Receiver mit, dass irgendwas...
   */
	virtual void graphDataUnSet( int type ) = 0;

  /**
   * 
   */
	virtual void syncGraphDataStarted(  ) = 0;

  /**
   * 
   */
	virtual void syncGraphDataFinished(  ) = 0;

};
#endif
