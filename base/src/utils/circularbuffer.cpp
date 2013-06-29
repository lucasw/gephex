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

#include "circularbuffer.h"

#include <stdexcept>
#include <cassert>

#include "buffer.h"

namespace utils
{
  static int max_(int a, int b)
  {
    return (a > b) ? a : b;
  }
  static int min_(int a, int b)
  {
    return (a < b) ? a : b;
  }

  static const int INITIAL_CAPACITY = 1024;
  static const double GROW_FACTOR = 1.5;

  CircularBuffer::CircularBuffer()
    : m_capacity(INITIAL_CAPACITY),
      m_begin(0), m_end(0),
      m_data(new unsigned char[m_capacity])
  {
  }

  CircularBuffer::~CircularBuffer()
  {
    delete[] m_data;
  }
	
  void CircularBuffer::push_back(const utils::Buffer& buf)
  {
    int len = this->len();
    int new_len = len + buf.getLen();

    // realloc
    if (new_len >= m_capacity)
      {
        int needed_capacity = max_(static_cast<int>(m_capacity*GROW_FACTOR),
                                   new_len) + 1;
        unsigned char* new_data = new unsigned char[needed_capacity];
        if (new_data == 0)
          throw std::runtime_error("Could not allocate memory");

        int l1 = min_(len, m_capacity - m_begin);
        memcpy(new_data, m_data + m_begin, l1);
        if (l1 < len)
          {
            int l2 = len - l1;
            memcpy(new_data + l1, m_data, l2);				
          }
			
        delete[] m_data;

        m_capacity = needed_capacity;
        m_begin    = 0;			
        m_data     = new_data;
        m_end      = len;
      }

    assert(new_len < m_capacity);


    int blen = buf.getLen();
    const unsigned char* bptr = buf.getPtr();

    int l1 = min_(m_capacity - m_end, blen);
    memcpy(m_data + m_end, bptr, l1);

    if (l1 < blen)
      {
        int l2 = blen - l1;
        memcpy(m_data, bptr+l1, l2);
        m_end = l2;
      }
    else
      {
        m_end += l1;
      }		

    assert(this->len() == new_len);

  }
	
  Buffer CircularBuffer::pop_front(int len)
  {
    if (len < 0 || len > this->len())
      throw std::invalid_argument("Wrong length at pop_front()");
		
    unsigned char* dst = new unsigned char[len];

    int l1 = min_(len, m_capacity - m_begin);
    memcpy(dst, m_data + m_begin, l1);

    if (l1 < len)
      {
        int l2 = len - l1;
        memcpy(dst + l1, m_data, l2);
        m_begin = l2;
      }
    else
      {
        m_begin = m_begin + l1;
      }

    if (m_begin == m_end)
      {
        m_begin = m_end = 0;
      }
		
    return utils::Buffer(dst, len, true);
  }
	
  int CircularBuffer::len() const
  {
    if (m_begin <= m_end)
      return m_end - m_begin;
    else
      return m_capacity - (m_begin - m_end);
  }

  void CircularBuffer::clear()
  {
    m_begin = m_end = 0;
  }
}
