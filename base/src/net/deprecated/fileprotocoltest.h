#ifndef INCLUDED_FILE_PROTOCOL_TEST_H
#define INCLUDED_FILE_PROTOCOL_TEST_H

#include "TestFramework/easytest.h"

class FileProtocolTest : public EasyTest
{
public:
  FileProtocolTest();
  virtual ~FileProtocolTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
