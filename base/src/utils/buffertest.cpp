#include "buffertest.h"

#include <iostream>

#include "buffer.h"
#include "block.h"


std::string BufferTest::getName() const
{
	return "BufferTest";
}

std::string BufferTest::getDescription() const
{
	return "";
}

void BufferTest::pre() throw(std::runtime_error)
{
}

void BufferTest::run() throw(std::runtime_error)
{
  // teste ob sich der buffer die daten kopiert
  std::string msg = "Hallo Kinder";
  utils::Buffer b((unsigned char*) msg.c_str(),msg.length()+1);

  msg = "00000";
  if (strcmp((const char*) b.getPtr(),"Hallo Kinder") != 0)
    throw std::runtime_error("Fehler");

  // teste + und += und =
  for (int size = 1; size <= 1024; size *= 2)
    {
      unsigned char* data = createRandomBlock(size*2);
      utils::Buffer b1(data,size);
      utils::Buffer b2(data+size,size);

      utils::Buffer b3 = b1 + b2;
      if (!compareBlocks(data,size*2,b3.getPtr(),b3.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}
  
      b1 += b2;
      if (!compareBlocks(data,size*2,b1.getPtr(),b1.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}

      b2 = b3;
      if (!compareBlocks(data,size*2,b2.getPtr(),b2.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}
      delete[] data;
    }

}

void BufferTest::post() throw(std::runtime_error)
{
}

