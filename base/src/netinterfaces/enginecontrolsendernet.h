#ifndef INCLUDED_ENGINECONTROL_SENDER_NET_H
#define INCLUDED_ENGINECONTROL_SENDER_NET_H

#include <string>

#include "interfaces/ienginecontrolsender.h"

#include "net/itaginterpreter.h"

class EngineControlSenderNet : public IEngineControlSender,
			      public net::ITagInterpreter<std::string>
{
public:
        EngineControlSenderNet();
	
	virtual void registerEngineControlReceiver(IEngineControlReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IEngineControlReceiver* m_rec;
};

#endif
