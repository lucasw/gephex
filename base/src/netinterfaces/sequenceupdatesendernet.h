#ifndef INCLUDED_SEQUENCEUPDATE_SENDER_NET_H
#define INCLUDED_SEQUENCEUPDATE_SENDER_NET_H

#include <string>

#include "interfaces/isequenceupdatesender.h"

#include "net/itaginterpreter.h"

class SequenceUpdateSenderNet : public ISequenceUpdateSender,
			      public net::ITagInterpreter<std::string>
{
public:
        SequenceUpdateSenderNet();
	
	virtual void registerSequenceUpdateReceiver(ISequenceUpdateReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	ISequenceUpdateReceiver* m_rec;
};

#endif
