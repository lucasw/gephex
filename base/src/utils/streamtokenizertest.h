#ifndef INCLUDED_STREAM_TOKENIZER_TEST_H
#define INCLUDED_STREAM_TOKENIZER_TEST_H

#include "../TestFramework/easytest.h"

class StreamTokenizerTest : public EasyTest
{
public:
  StreamTokenizerTest();
  virtual ~StreamTokenizerTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
