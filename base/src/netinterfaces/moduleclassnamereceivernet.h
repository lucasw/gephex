#ifndef INCLUDED_MODULECLASSNAMERECEIVERNET_H
#define INCLUDED_MODULECLASSNAMERECEIVERNET_H

#include "interfaces/imoduleclassnamereceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleClassNameReceiverNet : public IModuleClassNameReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleClassNameReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleClassNameReceiverNet();

	void moduleClassNameExists( const std::string& name );

};
#endif
