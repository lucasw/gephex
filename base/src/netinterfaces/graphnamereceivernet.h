#ifndef INCLUDED_GRAPHNAMERECEIVERNET_H
#define INCLUDED_GRAPHNAMERECEIVERNET_H

#include "interfaces/igraphnamereceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class GraphNameReceiverNet : public IGraphNameReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	GraphNameReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~GraphNameReceiverNet();

	void graphExists( const std::string& graphID, const std::string& snapID, const std::string& graphName, const std::string& snapName );

	void graphNoLongerExists( const std::string& graphID, const std::string& snapID );

	void graphRenamed( const std::string& graphID, const std::string& snapID, const std::string& newGraphName, const std::string& newSnapName );

};
#endif
