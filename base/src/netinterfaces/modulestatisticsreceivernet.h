#ifndef INCLUDED_MODULESTATISTICSRECEIVERNET_H
#define INCLUDED_MODULESTATISTICSRECEIVERNET_H

#include "interfaces/imodulestatisticsreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleStatisticsReceiverNet : public IModuleStatisticsReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleStatisticsReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleStatisticsReceiverNet();

	void modExecTimeSignal( int nodeID, double execTime );

};
#endif
