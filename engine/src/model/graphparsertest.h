#ifndef __GRAPH_PARSERTEST_H__
#define __GRAPH_PARSERTEST_H__

#include "TestFramework/easytest.h"

class GraphParserTest : public EasyTest
{
public:
  GraphParserTest();
  virtual ~GraphParserTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};



#endif
