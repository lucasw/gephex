#ifndef INCLUDED_LEAF_TEST_H
#define INCLUDED_LEAF_TEST_H
#include "Test.h"

class LeafTest : public Test
{
public:
	virtual void action(Tester&);

	virtual void pre() throw(std::runtime_error) = 0;
	virtual void run() throw(std::runtime_error) = 0;
	virtual void post() throw(std::runtime_error) = 0;
};

#endif

