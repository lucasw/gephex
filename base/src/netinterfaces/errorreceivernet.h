#ifndef INCLUDED_ERRORRECEIVERNET_H
#define INCLUDED_ERRORRECEIVERNET_H

#include "interfaces/ierrorreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ErrorReceiverNet : public IErrorReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ErrorReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ErrorReceiverNet();

	void error( const std::string& text );

	void warning( const std::string& text );

	void log( const std::string& text );

};
#endif
