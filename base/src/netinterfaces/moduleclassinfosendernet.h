#ifndef INCLUDED_MODULECLASSINFO_SENDER_NET_H
#define INCLUDED_MODULECLASSINFO_SENDER_NET_H

#include <string>

#include "interfaces/imoduleclassinfosender.h"

#include "net/itaginterpreter.h"

class ModuleClassInfoSenderNet : public IModuleClassInfoSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleClassInfoSenderNet();
	
	virtual void registerModuleClassInfoReceiver(IModuleClassInfoReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleClassInfoReceiver* m_rec;
};

#endif
