#ifndef INCLUDED_STRUCT_READER_TEST_H
#define INCLUDED_STRUCT_READER_TEST_H

#include "../TestFramework/easytest.h"

class StructReaderTest : public EasyTest
{
public:
  StructReaderTest();
  virtual ~StructReaderTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
