#ifndef INCLUDED_IMODULEDATARECEIVER_H
#define INCLUDED_IMODULEDATARECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleDataReceiver
{
public:
   /**
   * Teilt dem Receiver mit, dass irgendwas...
   */
	virtual void moduleDataSet( int modID, int type, const utils::Buffer& buf ) = 0;

   /**
   * Teilt dem Receiver mit, dass irgendwas...
   */
	virtual void moduleDataUnSet( int modID, int type ) = 0;

  /**
   * 
   */
	virtual void syncDataStarted(  ) = 0;

  /**
   * 
   */
	virtual void syncDataFinished(  ) = 0;

};
#endif
