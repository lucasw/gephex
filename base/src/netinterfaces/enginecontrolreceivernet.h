#ifndef INCLUDED_ENGINECONTROLRECEIVERNET_H
#define INCLUDED_ENGINECONTROLRECEIVERNET_H

#include "interfaces/ienginecontrolreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class EngineControlReceiverNet : public IEngineControlReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	EngineControlReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~EngineControlReceiverNet();

	void disconnect(  );

	void shutDown(  );

};
#endif
