#ifndef INCLUDED_RENDERERSTATUSRECEIVERNET_H
#define INCLUDED_RENDERERSTATUSRECEIVERNET_H

#include "interfaces/irendererstatusreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class RendererStatusReceiverNet : public IRendererStatusReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	RendererStatusReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~RendererStatusReceiverNet();

	void started(  );

	void stopped(  );

	void renderedGraphChanged( const std::string& graphID );

};
#endif
