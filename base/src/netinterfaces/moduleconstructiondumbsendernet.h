#ifndef INCLUDED_MODULECONSTRUCTIONDUMB_SENDER_NET_H
#define INCLUDED_MODULECONSTRUCTIONDUMB_SENDER_NET_H

#include <string>

#include "interfaces/imoduleconstructiondumbsender.h"

#include "net/itaginterpreter.h"

class ModuleConstructionDumbSenderNet : public IModuleConstructionDumbSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleConstructionDumbSenderNet();
	
	virtual void registerModuleConstructionDumbReceiver(IModuleConstructionDumbReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleConstructionDumbReceiver* m_rec;
};

#endif
