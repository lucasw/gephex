class LeafTest;
class CompositeTest;

//TODO sollte nicht so sein!
#include <iosfwd>

class Tester
{
public:
	virtual void performTest(LeafTest&) = 0;
	virtual void preTests(CompositeTest&) = 0;
	virtual void postTests(CompositeTest&) = 0;
};


class TesterStream : public Tester
{
public:
	TesterStream(std::ostream&);
	virtual ~TesterStream();

	virtual void performTest(LeafTest&);
	virtual void preTests(CompositeTest&);
	virtual void postTests(CompositeTest&);

private:
	std::ostream* m_s;
	int m_level;
};
