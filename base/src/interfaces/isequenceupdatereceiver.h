#ifndef INCLUDED_ISEQUENCEUPDATERECEIVER_H
#define INCLUDED_ISEQUENCEUPDATERECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISequenceUpdateReceiver
{
public:
  /**
   *
   */
	virtual void actionTimeChanged( int id, int newTime ) = 0;

  /**
   *
   */
	virtual void actionDeleted( int id ) = 0;

  /**
   *
   */
	virtual void actionAdded( int id, const std::string& command, int time ) = 0;

};
#endif
