#ifndef INCLUDED_MODULEDATARECEIVERNET_H
#define INCLUDED_MODULEDATARECEIVERNET_H

#include "interfaces/imoduledatareceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleDataReceiverNet : public IModuleDataReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleDataReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleDataReceiverNet();

	void moduleDataSet( int modID, int type, const utils::Buffer& buf );

	void moduleDataUnSet( int modID, int type );

	void syncDataStarted(  );

	void syncDataFinished(  );

};
#endif
