#ifndef INCLUDED_BUFFER_STREAM_TEST_H
#define INCLUDED_BUFFER_STREAM_TEST_H

#include "../TestFramework/easytest.h"

class BufferStreamTest : public EasyTest
{
public:
  BufferStreamTest();
  virtual ~BufferStreamTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
