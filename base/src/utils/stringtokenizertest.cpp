#include "stringtokenizertest.h"

#include "stringtokenizer.h"
//#include <iostream>

/*---------------------------------------------------------------------------*/

StringTokenizerTest::StringTokenizerTest()
  : EasyTest("StringTokenizerTest","")
{
}

StringTokenizerTest::~StringTokenizerTest()
{
}

void StringTokenizerTest::pre() throw(std::runtime_error)
{
}

void StringTokenizerTest::run() throw(std::runtime_error)
{
  utils::StringTokenizer st("Hallo, ein\ttest\nfuer st");
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
  if (token != "")
    throw std::runtime_error("Fehler6");
}

void StringTokenizerTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
