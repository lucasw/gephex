#ifndef INCLUDED_STRUCT_SCANNER_TEST_H
#define INCLUDED_STRUCT_SCANNER_TEST_H

#include "../TestFramework/easytest.h"

class StructScannerTest : public EasyTest
{
public:
  StructScannerTest();
  virtual ~StructScannerTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
