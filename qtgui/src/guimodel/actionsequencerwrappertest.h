#ifndef INCLUDED_ACTIONSEQUENCERWRAPPER_TOKENIZER_TEST_H
#define INCLUDED_ACTIONSEQUENCERWRAPPER_TOKENIZER_TEST_H

#include "TestFramework/easytest.h"

class ActionSequencerWrapperTest : public EasyTest
{
public:
  ActionSequencerWrapperTest();
  virtual ~ActionSequencerWrapperTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
