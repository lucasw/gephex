#ifndef INCLUDED_SEQUENCENAMERECEIVERNET_H
#define INCLUDED_SEQUENCENAMERECEIVERNET_H

#include "interfaces/isequencenamereceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class SequenceNameReceiverNet : public ISequenceNameReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	SequenceNameReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~SequenceNameReceiverNet();

	void sequenceExists( const std::string& id, const std::string& name );

	void sequenceNoLongerExists( const std::string& id );

	void sequenceRenamed( const std::string& id, const std::string& newName );

};
#endif
