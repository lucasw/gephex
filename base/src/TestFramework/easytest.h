#ifndef INCLUDED_EASY_TEST_H
#define INCLUDED_EASY_TEST_H
#include "LeafTest.h"

class EasyTest : public LeafTest
{
public:
  EasyTest(const std::string& name, const std::string& description);
  virtual ~EasyTest();

  virtual std::string getName() const;
  virtual std::string getDescription() const;

private:
  std::string m_name;
  std::string m_description;

  EasyTest(const EasyTest&); // not impl.
  const EasyTest& operator=(const EasyTest&); // not impl.
};

#endif

