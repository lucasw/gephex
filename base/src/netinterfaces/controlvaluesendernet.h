#ifndef INCLUDED_CONTROLVALUE_SENDER_NET_H
#define INCLUDED_CONTROLVALUE_SENDER_NET_H

#include <string>

#include "interfaces/icontrolvaluesender.h"

#include "net/itaginterpreter.h"

class ControlValueSenderNet : public IControlValueSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ControlValueSenderNet();
	
	virtual void registerControlValueReceiver(IControlValueReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IControlValueReceiver* m_rec;
};

#endif
