#ifndef INCLUDED_MODELSTATUS_SENDER_NET_H
#define INCLUDED_MODELSTATUS_SENDER_NET_H

#include <string>

#include "interfaces/imodelstatussender.h"

#include "net/itaginterpreter.h"

class ModelStatusSenderNet : public IModelStatusSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModelStatusSenderNet();
	
	virtual void registerModelStatusReceiver(IModelStatusReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModelStatusReceiver* m_rec;
};

#endif
