#ifndef INCLUDED_MODELCONTROL_SENDER_NET_H
#define INCLUDED_MODELCONTROL_SENDER_NET_H

#include <string>

#include "interfaces/imodelcontrolsender.h"

#include "net/itaginterpreter.h"

class ModelControlSenderNet : public IModelControlSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModelControlSenderNet();
	
	virtual void registerModelControlReceiver(IModelControlReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModelControlReceiver* m_rec;
};

#endif
