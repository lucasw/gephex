#ifndef INCLUDED_IMODELSTATUSRECEIVER_H
#define INCLUDED_IMODELSTATUSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModelStatusReceiver
{
public:
  /**
   *
   */	 
	virtual void editGraphChanged( const std::string& graphID, const std::string& snapID ) = 0;

};
#endif
