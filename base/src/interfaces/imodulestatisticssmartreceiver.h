#ifndef INCLUDED_IMODULESTATISTICSSMARTRECEIVER_H
#define INCLUDED_IMODULESTATISTICSSMARTRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleStatisticsSmartReceiver
{
public:
/**
 * Die Berechnungsroutine kann ueber dieses signal die
 * Berechnungsdauer einzelner Module melden
 */
	virtual void modExecTimeSignal( const std::string& graphName, int nodeID, double execTime ) = 0;

};
#endif
