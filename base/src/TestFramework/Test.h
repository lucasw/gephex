#ifndef INCLUDED_TEST
#define INCLUDED_TEST

#include <stdexcept>
#include <string>

class Tester;

class Test
{
public:
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;

	virtual void action(Tester&) = 0;
};

#endif

