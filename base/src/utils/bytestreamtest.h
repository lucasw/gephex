#ifndef INCLUDED_BYTE_STREAM_TEST_H
#define INCLUDED_BYTE_STREAM_TEST_H

#include "TestFramework/easytest.h"

class ByteStreamTest : public EasyTest
{
public:
  ByteStreamTest();
  virtual ~ByteStreamTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
