#include "xmlutilstest.h"

#include <iostream>

#include "xmlutils.h"
#include "block.h"


std::string XmlutilsTest::getName() const
{
	return "XmlutilsTest";
}

std::string XmlutilsTest::getDescription() const
{
	return "";
}

void XmlutilsTest::pre() throw(std::runtime_error)
{
}

void test1()
{
  std::string test_text = "<das> <ist> der erste Test </ist> </das>";

  utils::xml::Iterator i = test_text.begin();
  utils::xml::Iterator end = test_text.end();

  std::string blubb;
  i = utils::xml::tagOpens(i, end, "das");
  i = utils::xml::leafTag(i, end, "ist", blubb);
  i = utils::xml::tagCloses(i, end, "das");
  
  if (i != end)
    throw std::runtime_error("Should have reached end of input");

  if (blubb != " der erste Test ")
    throw std::runtime_error((std::string("blubb wrong: ") + blubb).c_str());
}

void test2()
{
  std::string test_text = "< das > <ist  >der erste Test</  ist> < /das>";

  utils::xml::Iterator i = test_text.begin();
  utils::xml::Iterator end = test_text.end();

  std::string blubb;
  i = utils::xml::tagOpens(i, end, "das");
  i = utils::xml::leafTag(i, end, "ist", blubb);
  i = utils::xml::tagCloses(i, end, "das");
  
  if (i != end)
    throw std::runtime_error("Should have reached end of input");

  if (blubb != "der erste Test")
    throw std::runtime_error((std::string("blubb wrong: ") + blubb).c_str());
}

void test3()
{
  std::string test_text = "  <bumm>";
  std::string tag = utils::xml::next_tag_name(test_text.begin(),
                                              test_text.end());

  if (tag != "bumm")
    throw std::runtime_error((std::string("tag is '") + tag 
                              + std::string(" but should be 'bumm'")).c_str());
}
void XmlutilsTest::run() throw(std::runtime_error)
{
  test1();
  test2();
  test3();
}

void XmlutilsTest::post() throw(std::runtime_error)
{
}

