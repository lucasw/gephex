#ifndef INCLUDED_SEQUENCEUPDATERECEIVERNET_H
#define INCLUDED_SEQUENCEUPDATERECEIVERNET_H

#include "interfaces/isequenceupdatereceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class SequenceUpdateReceiverNet : public ISequenceUpdateReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	SequenceUpdateReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~SequenceUpdateReceiverNet();

	void actionTimeChanged( int id, int newTime );

	void actionDeleted( int id );

	void actionAdded( int id, const std::string& command, int time );

};
#endif
