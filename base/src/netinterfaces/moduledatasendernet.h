#ifndef INCLUDED_MODULEDATA_SENDER_NET_H
#define INCLUDED_MODULEDATA_SENDER_NET_H

#include <string>

#include "interfaces/imoduledatasender.h"

#include "net/itaginterpreter.h"

class ModuleDataSenderNet : public IModuleDataSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleDataSenderNet();
	
	virtual void registerModuleDataReceiver(IModuleDataReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleDataReceiver* m_rec;
};

#endif
