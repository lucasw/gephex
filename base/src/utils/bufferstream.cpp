/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "bufferstream.h"

#include "buffer.h"

namespace utils
{

  class Buffer_streambuf : public std::streambuf
  {
    typedef std::streambuf inherited;
    typedef int int_type;
    typedef std::streamsize streamsize;

    Buffer& _buf;
    char  _cache[256];
  
  public:
    Buffer_streambuf(Buffer& str);
  
  protected:
    virtual int sync();
    virtual int_type overflow(int_type c = EOF);

  private:
    void initInOutBuffer(int pos);
  };

  void Buffer_streambuf::initInOutBuffer(int pos)
  {
    char* gbuf 
      = reinterpret_cast<char*>(const_cast<unsigned char*>(_buf.getPtr()));
    setg(gbuf, gbuf + pos, gbuf+_buf.getLen());
    setp(_cache, _cache + sizeof(_cache));
  }


  Buffer_streambuf::Buffer_streambuf(Buffer& buf)
    : _buf(buf)
  {
    initInOutBuffer(0);
  }


  int Buffer_streambuf::sync()
  {
    size_t l = pptr() - pbase();
    if (l > 0) 
      {
	size_t pos = gptr() - eback();  // remember the get position
	_buf += Buffer(reinterpret_cast<unsigned char*>(_cache), l);
	initInOutBuffer(pos);
      }
    return 0;
  }

  Buffer_streambuf::int_type
  Buffer_streambuf::overflow(int_type c)
  {
    sync();
    if (c != EOF) 
      {
	*_cache = c;
	pbump(1);
	return c;
      }
    return 1;
  }


  IBufferStream::IBufferStream(const Buffer& b)
    : inherited(new Buffer_streambuf(const_cast<Buffer&>(b)))
  {
  }

  IBufferStream::~IBufferStream()
  {
    delete rdbuf();
  }


  OBufferStream::OBufferStream(Buffer& b)
    : inherited(new Buffer_streambuf(b))
  {
  }

  OBufferStream::~OBufferStream()
  {
    delete rdbuf();
  }
}

