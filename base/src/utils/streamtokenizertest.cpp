#include "streamtokenizertest.h"

#include "streamtokenizer.h"

#include <sstream>
//#include <iostream>

/*---------------------------------------------------------------------------*/

StreamTokenizerTest::StreamTokenizerTest()
  : EasyTest("StreamTokenizerTest","")
{
}

StreamTokenizerTest::~StreamTokenizerTest()
{
}

void StreamTokenizerTest::pre() throw(std::runtime_error)
{
}

void StreamTokenizerTest::run() throw(std::runtime_error)
{
  std::istringstream stream("Hallo, ein\ttest\nfuer st     \nream");
  utils::StreamTokenizer st(stream);
  std::string token;

  token = st.next("\n\t\r ");
  if (token != "Hallo,")
    throw std::runtime_error("Fehler1");

  token = st.next("\n\t\r ");
  if (token != "ein")
    throw std::runtime_error((token + " (expected ein)").c_str());

  token = st.next(" \n\t\r");
  if (token != "test")
    throw std::runtime_error("Fehler3");

  token = st.next(" \n\t\r");
  if (token != "fuer")
    throw std::runtime_error("Fehler4");

  token = st.next(" \n\t\r");
  if (token != "st")
    throw std::runtime_error("Fehler5");

  token = st.next(" \n\t\r");
  if (token != "ream")
    throw std::runtime_error("Fehler6");

  token = st.next(" \n\t\r");
  if (token != "")
    throw std::runtime_error("Fehler7");
}

void StreamTokenizerTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
