#ifndef INCLUDED_SEQUENCERSTATUS_SENDER_NET_H
#define INCLUDED_SEQUENCERSTATUS_SENDER_NET_H

#include <string>

#include "interfaces/isequencerstatussender.h"

#include "net/itaginterpreter.h"

class SequencerStatusSenderNet : public ISequencerStatusSender,
			      public net::ITagInterpreter<std::string>
{
public:
        SequencerStatusSenderNet();
	
	virtual void registerSequencerStatusReceiver(ISequencerStatusReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	ISequencerStatusReceiver* m_rec;
};

#endif
