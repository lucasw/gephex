#ifndef INCLUDED_GRAPHDATA_SENDER_NET_H
#define INCLUDED_GRAPHDATA_SENDER_NET_H

#include <string>

#include "interfaces/igraphdatasender.h"

#include "net/itaginterpreter.h"

class GraphDataSenderNet : public IGraphDataSender,
			      public net::ITagInterpreter<std::string>
{
public:
        GraphDataSenderNet();
	
	virtual void registerGraphDataReceiver(IGraphDataReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IGraphDataReceiver* m_rec;
};

#endif
