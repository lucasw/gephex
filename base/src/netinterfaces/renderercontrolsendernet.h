#ifndef INCLUDED_RENDERERCONTROL_SENDER_NET_H
#define INCLUDED_RENDERERCONTROL_SENDER_NET_H

#include <string>

#include "interfaces/irenderercontrolsender.h"

#include "net/itaginterpreter.h"

class RendererControlSenderNet : public IRendererControlSender,
			      public net::ITagInterpreter<std::string>
{
public:
        RendererControlSenderNet();
	
	virtual void registerRendererControlReceiver(IRendererControlReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IRendererControlReceiver* m_rec;
};

#endif
