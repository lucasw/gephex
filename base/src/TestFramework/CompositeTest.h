#ifndef INCLUDED_COMPOSITE_TEST_H
#define INCLUDED_COMPOSITE_TEST_H

#include "Test.h"
#include <list>

class CompositeTest : public Test
{
public:
	CompositeTest(std::string name,std::string description);
	virtual ~CompositeTest();

	virtual std::string getName() const;
	virtual std::string getDescription() const;

	virtual void addTest(Test&);

	virtual void action(Tester&);

private:
	std::list<Test*> m_tests;
	std::string m_name;
	std::string m_description;
};

#endif
