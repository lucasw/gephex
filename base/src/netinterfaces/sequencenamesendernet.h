#ifndef INCLUDED_SEQUENCENAME_SENDER_NET_H
#define INCLUDED_SEQUENCENAME_SENDER_NET_H

#include <string>

#include "interfaces/isequencenamesender.h"

#include "net/itaginterpreter.h"

class SequenceNameSenderNet : public ISequenceNameSender,
			      public net::ITagInterpreter<std::string>
{
public:
        SequenceNameSenderNet();
	
	virtual void registerSequenceNameReceiver(ISequenceNameReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	ISequenceNameReceiver* m_rec;
};

#endif
