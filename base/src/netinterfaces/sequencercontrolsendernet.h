#ifndef INCLUDED_SEQUENCERCONTROL_SENDER_NET_H
#define INCLUDED_SEQUENCERCONTROL_SENDER_NET_H

#include <string>

#include "interfaces/isequencercontrolsender.h"

#include "net/itaginterpreter.h"

class SequencerControlSenderNet : public ISequencerControlSender,
			      public net::ITagInterpreter<std::string>
{
public:
        SequencerControlSenderNet();
	
	virtual void registerSequencerControlReceiver(ISequencerControlReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	ISequencerControlReceiver* m_rec;
};

#endif
