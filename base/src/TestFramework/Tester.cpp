#include "Tester.h"

#include "LeafTest.h"
#include "CompositeTest.h"

#include <iostream>


TesterStream::TesterStream(std::ostream& s)
 : m_s(&s), m_level(0)
{
}

TesterStream::~TesterStream()
{
}

void TesterStream::performTest(LeafTest& lt)
{
	std::string spaces = "";
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Test: " << lt.getName() << std::endl;
	(*m_s) << spaces << lt.getDescription() << std::endl;

	try 
	{
		lt.pre();
	}
	catch (std::runtime_error& e)
	{
		(*m_s) << spaces <<"FAIL at pre(): " << e.what() << std::endl;
		lt.post(); //TODO
		return;
	}
	try 
	{
		lt.run();
	}
	catch (std::runtime_error& e)
	{
		(*m_s) << spaces <<"FAIL at run(): " << e.what() << std::endl;
		lt.post(); //TODO
		return;
	}
	try 
	{
		lt.post();
	}
	catch (std::runtime_error& e)
	{
		(*m_s) << spaces <<"FAIL at post(): " << e.what() << std::endl;
		return;
	}

	(*m_s) << spaces <<"OK" << std::endl;
}

void TesterStream::preTests(CompositeTest& ct)
{
	std::string spaces = "";
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Starting Test Group: " << ct.getName() << std::endl << ct.getDescription() << std::endl;
	++m_level;
}

void TesterStream::postTests(CompositeTest& ct)
{
	--m_level;
	std::string spaces;
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Finished Test Group: " << ct.getName() << std::endl;
}
