#ifndef INCLUDED_MODULECLASSNAME_SENDER_NET_H
#define INCLUDED_MODULECLASSNAME_SENDER_NET_H

#include <string>

#include "interfaces/imoduleclassnamesender.h"

#include "net/itaginterpreter.h"

class ModuleClassNameSenderNet : public IModuleClassNameSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleClassNameSenderNet();
	
	virtual void registerModuleClassNameReceiver(IModuleClassNameReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleClassNameReceiver* m_rec;
};

#endif
