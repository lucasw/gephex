#include "buffer.h"
#include <cstring>

#if defined(HAVE_CONFIG_H)
  #include "config.h"
#endif

// for the min and max templates
#if defined (COMP_VC)
  #include "minmax.h"
#else 
  #include <algorithm>   
#endif

namespace
{
  const double GROW_FACTOR = 1.2;
}

namespace utils
{  
  using std::max;
  Buffer::Buffer(int maxLengthHint)
    : m_buffer(0), m_len(0), m_capacity(max(0,maxLengthHint))
  {
    if (m_capacity > 0)
      m_buffer = new unsigned char[m_capacity];
  }

  Buffer::Buffer(const unsigned char* b, int l,
	             int maxLengthHint)
    : m_len(l),
      m_capacity(max(l,maxLengthHint))
  {	
       m_buffer = new unsigned char[m_capacity];
       memcpy(m_buffer,b,m_len);
  }

  Buffer::Buffer(unsigned char* b, int l, bool owner, 
	             int maxLengthHint)
    : m_len(l),
      m_capacity(max(l,maxLengthHint))
  {
	if (!owner)
	{
       m_buffer = new unsigned char[m_capacity];
       memcpy(m_buffer,b,m_len);
	}
	else
	{
	   m_buffer = b;
	}
  }

  Buffer::Buffer(const Buffer& b)
    : m_buffer(new unsigned char[b.getLen()]), m_len(b.getLen()),
      m_capacity(m_len)
  {
    memcpy(m_buffer,b.getPtr(),m_len);
  }

  Buffer::Buffer(const Buffer& b, int maxLengthHint)
    : m_buffer(new unsigned char[max(b.getLen(), maxLengthHint)]), m_len(b.getLen()),
      m_capacity(max(b.getLen(), maxLengthHint))
  {
    memcpy(m_buffer,b.getPtr(),m_len);
  }

  Buffer& Buffer::operator=(const Buffer& b)
  {
    if (this != &b)
      {
	if (b.getLen() > m_capacity)
	  {
	    delete[] m_buffer;
	    m_capacity = (int) (b.getLen() * GROW_FACTOR);
	    m_buffer = new unsigned char[m_capacity];
	  }

	m_len = b.getLen();
	memcpy(m_buffer,b.getPtr(),m_len);
      }

    return *this;
  }

  Buffer& Buffer::operator+=(const Buffer& b)
  {
    int newLen = this->getLen() + b.getLen();

    if (newLen > m_capacity)
      {
	m_capacity = (int) (newLen*GROW_FACTOR);
	unsigned char* newData = new unsigned char[m_capacity];
	memcpy(newData,this->getPtr(),this->getLen());
	memcpy(newData+this->getLen(),b.getPtr(),b.getLen());
	delete[] m_buffer;
	m_buffer = newData;
	//		std::cerr << "resize" << std::endl;
      }
    else
      {
	memcpy(m_buffer+this->getLen(), b.getPtr(), b.getLen());
      }
  
    m_len = newLen;

    return *this;
  }


  Buffer Buffer::operator+(const Buffer& b) const
  {
    Buffer newBuf(*this, m_len + b.getLen());
    newBuf += b;
    return newBuf;
  }

  Buffer::~Buffer()
  {
    delete[] m_buffer;
  }

  const unsigned char* Buffer::getPtr() const
  {
    return m_buffer;
  }

  int Buffer::getLen() const
  {
    return m_len;
  }

  /*void Buffer::setData(const unsigned char* data, int len)
    {
    // alten loeschen
    delete[] m_buffer;

    // neu anlegen
    m_buffer = new unsigned char[len];
    m_len=len;

    // und kopieren
    memcpy(m_buffer,data,m_len);
    }*/

}
