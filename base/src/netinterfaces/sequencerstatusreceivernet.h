#ifndef INCLUDED_SEQUENCERSTATUSRECEIVERNET_H
#define INCLUDED_SEQUENCERSTATUSRECEIVERNET_H

#include "interfaces/isequencerstatusreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class SequencerStatusReceiverNet : public ISequencerStatusReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	SequencerStatusReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~SequencerStatusReceiverNet();

	void editSequenceChanged( const std::string& sequenceID );

	void started(  );

	void stopped(  );

	void paused(  );

	void time( int currentTime );

};
#endif
