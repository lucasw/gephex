#ifndef INCLUDED_MODELSTATUSRECEIVERNET_H
#define INCLUDED_MODELSTATUSRECEIVERNET_H

#include "interfaces/imodelstatusreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModelStatusReceiverNet : public IModelStatusReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModelStatusReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModelStatusReceiverNet();

	void editGraphChanged( const std::string& graphID, const std::string& snapID );

};
#endif
