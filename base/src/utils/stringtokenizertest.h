#ifndef INCLUDED_STRING_TOKENIZER_TEST_H
#define INCLUDED_STRING_TOKENIZER_TEST_H

#include "TestFramework/easytest.h"

class StringTokenizerTest : public EasyTest
{
public:
  StringTokenizerTest();
  virtual ~StringTokenizerTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
