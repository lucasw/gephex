#include "xpm.h"

#include <cstring>
#include <stdexcept>

namespace gui
{
	
  namespace
  {
    void copy(char**& m_ptr, int& m_len, char** ptr, int len)
    {
      m_len = len;
      m_ptr = new char*[m_len];
			
      for (int i = 0; i < m_len; ++i)
        {
          int currentLen = strlen(ptr[i])+1;
          m_ptr[i] = new char[currentLen];
          memcpy(m_ptr[i],ptr[i],currentLen);
        }
    }
		
    void kill(char**& m_ptr, int& m_len)
    {
      for (int i = 0; i < m_len; ++i)
        {
          delete[] m_ptr[i];
        }
			
      delete[] m_ptr;
      m_len = 0;
    }	
  }
	
  Xpm::Xpm(const Xpm& x)
  {
    copy(m_ptr, m_len, x.m_ptr,x.m_len);
  }

  int safe_strlen(const char* str, int max_len)
  {
    int len = 0;
    if (max_len <= 0)
      return -1;

    while (len < max_len && str[len] != 0)
      {
        ++len;
      }

    return len;
  }

  Xpm::Xpm(const char* ptr, int len)
  {
    const char* offset = ptr;		
    int index = 0;
    while (offset - ptr < len)
      {
        ++index;
        int current_len = safe_strlen(offset, len - (offset - ptr));
        if (current_len == -1)
          throw std::runtime_error("Invalid data at Xpm::Xpm()");
        offset += current_len + 1;
      }
		
    //if (offset - ptr > len)
    //printf("Ich protestiere!\n");

    m_ptr = new char*[index];
    m_len = index;
		
    offset = ptr;
    index = 0;
    while (offset - ptr < len)
      {
        int current_len = safe_strlen(offset, len - (offset - ptr));
        if (current_len == -1)
          throw std::runtime_error("Invalid data at Xpm::Xpm()");
        m_ptr[index] = new char[current_len+1];
        memcpy(m_ptr[index], offset, current_len+1);

        offset += current_len+1;
        ++index;
      }
  }
	
  Xpm::~Xpm()
  {
    kill(m_ptr, m_len);
  }
	
  const Xpm& Xpm::operator=(const Xpm& x)
  {
    if (this == &x)
      return *this;
		
    kill(m_ptr, m_len);
    copy(m_ptr, m_len,x.m_ptr,x.m_len);
    return *this;
  }
	
  const char** Xpm::getPtr() const
  {
    return const_cast<const char**>(m_ptr);
  }
} // end of namespace gui
