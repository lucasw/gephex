#ifndef INCLUDED_MODULECONSTRUCTIONDUMBRECEIVERNET_H
#define INCLUDED_MODULECONSTRUCTIONDUMBRECEIVERNET_H

#include "interfaces/imoduleconstructiondumbreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModuleConstructionDumbReceiverNet : public IModuleConstructionDumbReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModuleConstructionDumbReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModuleConstructionDumbReceiverNet();

	void moduleAdded( const std::string& moduleClassName, int modID );

	void modulesConnected( int moduleID1, int outputIndex, int moduleID2, int inputIndex );

	void modulesDisconnected( int moduleID, int inputIndex );

	void moduleDeleted( int moduleID );

	void syncModuleStarted(  );

	void syncModuleFinished(  );

};
#endif
