#ifndef INCLUDED_IMODULESTATISTICSRECEIVER_H
#define INCLUDED_IMODULESTATISTICSRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleStatisticsReceiver
{
public:
 /**
  * Die Berechnungsroutine kann ueber dieses signal die
  * Berechnungsdauer einzelner Module melden
  */
	virtual void modExecTimeSignal( int nodeID, double execTime ) = 0;

};
#endif
