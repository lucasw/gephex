#ifndef INCLUDED_MODULECLASSLOADERCONTROL_SENDER_NET_H
#define INCLUDED_MODULECLASSLOADERCONTROL_SENDER_NET_H

#include <string>

#include "interfaces/imoduleclassloadercontrolsender.h"

#include "net/itaginterpreter.h"

class ModuleClassLoaderControlSenderNet : public IModuleClassLoaderControlSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleClassLoaderControlSenderNet();
	
	virtual void registerModuleClassLoaderControlReceiver(IModuleClassLoaderControlReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleClassLoaderControlReceiver* m_rec;
};

#endif
