#ifndef INCLUDED_MODULECLASSINFORECEIVERNET_H
#define INCLUDED_MODULECLASSINFORECEIVERNET_H

#include "interfaces/imoduleclassinforeceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleClassInfoReceiverNet : public IModuleClassInfoReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleClassInfoReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleClassInfoReceiverNet();

	void moduleClassLoaded( const std::string& moduleClassName, const utils::Buffer& buf );

	void moduleClassUnloaded( const std::string& moduleClassID );

	void syncStarted(  );

	void syncFinished(  );

};
#endif
