#ifndef __SEQUENCERTEST_H__
#define __SEQUENCERTEST_H__

#include "TestFramework/LeafTest.h"


class SequencerTest: public LeafTest
{
public:
	virtual std::string getName() const;
	virtual std::string getDescription() const;

	virtual void pre() throw(std::runtime_error);

	virtual void run() throw(std::runtime_error);

	virtual void post() throw(std::runtime_error);
};


#endif
