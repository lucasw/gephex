#ifndef INCLUDED_RENDERERSTATUS_SENDER_NET_H
#define INCLUDED_RENDERERSTATUS_SENDER_NET_H

#include <string>

#include "interfaces/irendererstatussender.h"

#include "net/itaginterpreter.h"

class RendererStatusSenderNet : public IRendererStatusSender,
			      public net::ITagInterpreter<std::string>
{
public:
        RendererStatusSenderNet();
	
	virtual void registerRendererStatusReceiver(IRendererStatusReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IRendererStatusReceiver* m_rec;
};

#endif
