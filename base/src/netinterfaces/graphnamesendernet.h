#ifndef INCLUDED_GRAPHNAME_SENDER_NET_H
#define INCLUDED_GRAPHNAME_SENDER_NET_H

#include <string>

#include "interfaces/igraphnamesender.h"

#include "net/itaginterpreter.h"

class GraphNameSenderNet : public IGraphNameSender,
			      public net::ITagInterpreter<std::string>
{
public:
        GraphNameSenderNet();
	
	virtual void registerGraphNameReceiver(IGraphNameReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IGraphNameReceiver* m_rec;
};

#endif
