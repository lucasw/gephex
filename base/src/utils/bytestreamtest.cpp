#include "bytestreamtest.h"

#include "inbytestream.h"
#include "outbytestream.h"
#include "inbytestreamutils.h"
#include "outbytestreamutils.h"
//#include <iostream>

#include "buffer.h"
/*---------------------------------------------------------------------------*/

ByteStreamTest::ByteStreamTest()
  : EasyTest("ByteStreamTest","")
{
}

ByteStreamTest::~ByteStreamTest()
{
}

void ByteStreamTest::pre() throw(std::runtime_error)
{
}

void ByteStreamTest::run() throw(std::runtime_error)
{
  utils::OutByteStream obs;
  obs << 1 << "Hallo";
  
  utils::InByteStream ibs(obs.getBuffer());
  int test;
  std::string str;
  ibs >> test >> str;

  if (test != 1 || str != "Hallo")
    throw std::runtime_error("Juhu");
}

void ByteStreamTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
