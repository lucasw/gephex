#include "autoptrtest.h"

#include <list>

#include "autoptr.h"

class DoofesDing
{
public:
  DoofesDing(bool& b)
    : m_b(b)
  {
    m_b = false;
  }

  ~DoofesDing()
  {
    m_b = true;
  }

private:
  bool& m_b;
};

std::string AutoPtrTest::getName() const
{
	return "AutoPtrTest";
}

std::string AutoPtrTest::getDescription() const
{
	return "";
}

void AutoPtrTest::pre() throw(std::runtime_error)
{
}

void AutoPtrTest::run() throw(std::runtime_error)
{
  bool destroyed = false;

  {
    utils::AutoPtr<DoofesDing> p1(new DoofesDing(destroyed));
    {
      utils::AutoPtr<DoofesDing> p2 = p1;
    }

    if (destroyed)
      {
		throw std::runtime_error("Fehler!!");
      }
  }

  if (!destroyed)
    {
      throw std::runtime_error("Fehler!!");
    }

  utils::AutoPtr<int> p(new int(100));

  if (*p != 100)
    throw std::runtime_error("Fehler!!");

  utils::AutoPtr<std::list<int> > p2(new std::list<int>());
  
  if (p2->size() != 0)
    throw std::runtime_error("Fehler!!");
}

void AutoPtrTest::post() throw(std::runtime_error)
{
}

