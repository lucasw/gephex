#ifndef INCLUDED_MODULECLASSLOADERCONTROLRECEIVERNET_H
#define INCLUDED_MODULECLASSLOADERCONTROLRECEIVERNET_H

#include "interfaces/imoduleclassloadercontrolreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleClassLoaderControlReceiverNet : public IModuleClassLoaderControlReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleClassLoaderControlReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleClassLoaderControlReceiverNet();

	void loadModuleClass( const std::string& name );

	void unloadModuleClass( const std::string& name );

	void synchronize(  );

};
#endif
