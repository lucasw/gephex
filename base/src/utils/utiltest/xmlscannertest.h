#ifndef INCLUDED_XML_SCANNER_TEST_H
#define INCLUDED_XML_SCANNER_TEST_H

#include "../TestFramework/easytest.h"

class XMLScannerTest : public EasyTest
{
public:
  XMLScannerTest();
  virtual ~XMLScannerTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif