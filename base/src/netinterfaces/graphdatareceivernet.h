#ifndef INCLUDED_GRAPHDATARECEIVERNET_H
#define INCLUDED_GRAPHDATARECEIVERNET_H

#include "interfaces/igraphdatareceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class GraphDataReceiverNet : public IGraphDataReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	GraphDataReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~GraphDataReceiverNet();

	void graphDataSet( int type, const utils::Buffer& buf );

	void graphDataUnSet( int type );

	void syncGraphDataStarted(  );

	void syncGraphDataFinished(  );

};
#endif
