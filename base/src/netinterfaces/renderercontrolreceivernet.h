#ifndef INCLUDED_RENDERERCONTROLRECEIVERNET_H
#define INCLUDED_RENDERERCONTROLRECEIVERNET_H

#include "interfaces/irenderercontrolreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class RendererControlReceiverNet : public IRendererControlReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	RendererControlReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~RendererControlReceiverNet();

	void start(  );

	void stop(  );

	void setInputValue( const std::string& graphName, int nodeID, int inputIndex, const utils::Buffer& buf );

	void syncInputValue( const std::string& graphName, int nodeID, int inputIndex );

	void synchronizeInputValues( const std::string& graphName );

	void synchronize(  );

};
#endif
