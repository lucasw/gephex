#ifndef INCLUDED_ERROR_SENDER_NET_H
#define INCLUDED_ERROR_SENDER_NET_H

#include <string>

#include "interfaces/ierrorsender.h"

#include "net/itaginterpreter.h"

class ErrorSenderNet : public IErrorSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ErrorSenderNet();
	
	virtual void registerErrorReceiver(IErrorReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IErrorReceiver* m_rec;
};

#endif
