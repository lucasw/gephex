#include "LeafTest.h"
#include "CompositeTest.h"
#include "Tester.h"

#include <iostream>

class MyTest : public LeafTest
{
public:
	virtual std::string getName() const
	{
		return "Test1";
	}

	virtual std::string getDescription() const
	{
		return "Ein wichtiger Test";
	}

	virtual void pre() throw(std::runtime_error)
	{
	}

	virtual void run() throw(std::runtime_error)
	{
		throw std::runtime_error("Hallo");
	}

	virtual void post() throw(std::runtime_error)
	{
	}
};

int main(int argc,char* argv[])
{

	MyTest t1, t2;
	TesterStream ts(std::cout);
	
	CompositeTest ct("Compo","Ja");

	ct.addTest(t1);
	ct.addTest(t2);

	ct.action(ts);

	return 0;
}

