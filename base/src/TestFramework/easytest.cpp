#include "easytest.h"

EasyTest::EasyTest(const std::string& name, const std::string& description)
  : m_name(name), m_description(description)
{
}

EasyTest::~EasyTest()
{
}

std::string EasyTest::getName() const
{
  return m_name;
}

std::string EasyTest::getDescription() const
{
  return m_description;
}

