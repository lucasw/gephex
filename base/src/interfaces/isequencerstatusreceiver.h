#ifndef INCLUDED_ISEQUENCERSTATUSRECEIVER_H
#define INCLUDED_ISEQUENCERSTATUSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISequencerStatusReceiver
{
public:
  /**
   *
   */	 
	virtual void editSequenceChanged( const std::string& sequenceID ) = 0;

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
	virtual void paused(  ) = 0;

  /**
   *
   */
	virtual void time( int currentTime ) = 0;

};
#endif
