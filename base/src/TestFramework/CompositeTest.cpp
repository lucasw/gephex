#include "CompositeTest.h"
#include "Tester.h"

CompositeTest::CompositeTest(std::string name,std::string description)
	: m_name(name), m_description(description)
{
}

CompositeTest::~CompositeTest()
{
}

void CompositeTest::action(Tester& t)
{
  t.preTests(*this);

  for (std::list<Test*>::iterator i = m_tests.begin(); i != m_tests.end(); ++i)
    {
      (*i)->action(t);
    }

  t.postTests(*this);
}

std::string CompositeTest::getName() const
{
	return m_name;
}

std::string CompositeTest::getDescription() const
{
	return m_description;
}

void CompositeTest::addTest(Test& t)
{
	m_tests.push_back(&t);
}
