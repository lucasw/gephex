#include "inbytestream.h"

//TODO needed for memcpy
//#ifdef OS_WIN32
#include <cstring>
//#endif

#include "buffer.h"

namespace utils
{


    InByteStream::InByteStream(const utils::Buffer& b)
      : begin(new unsigned char[b.getLen()]), end(begin + b.getLen()),
	current(begin)
    {
		memcpy(begin,b.getPtr(), b.getLen());      
    }

    InByteStream::~InByteStream()
    {
      delete[] begin;
    }
    
    bool InByteStream::hasMore() const
    {
      return current != end;
    }

    unsigned char InByteStream::get()
    {
      if (current < end)
	{
	  unsigned char last = *current;
	  ++current;
	  return last;
	}

      return 0;
    }

    void InByteStream::unget()
    {
      if (current > begin)
	--current;
	
    }


}
