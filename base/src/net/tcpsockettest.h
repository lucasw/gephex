#ifndef INCLUDED_TCP_SOCKET_TEST_H
#define INCLUDED_TCP_SOCKET_TEST_H

#include "TestFramework/LeafTest.h"

class TCPSocketTest : public LeafTest
{

public:
	virtual std::string getName() const;
	virtual std::string getDescription() const;

	virtual void pre() throw(std::runtime_error);

	virtual void run() throw(std::runtime_error);

	virtual void post() throw(std::runtime_error);
};




#endif
