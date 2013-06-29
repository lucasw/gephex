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

#ifndef INCLUDED_CIRCULAR_BUFFER_H
#define INCLUDED_CIRCULAR_BUFFER_H

namespace utils
{
  class Buffer;

  /**
   * The circular buffer stores unsigned char data.
   * It supports two operations: push back n bytes and pop m bytes
   * from the front.
   *
   * pop_front is linear in the number of bytes.
   * push_back is linear if no resizing is needed.
   * If the buffer has to grow, pushing back n bytes costs
   * O(n log(n)).
   *
   * len and clear are constant time operations.
   */
  class CircularBuffer
  {
  public:
    /**
     * 
     */
    CircularBuffer();
    ~CircularBuffer();

    /**
     *
     */
    void push_back(const utils::Buffer& buf);

    /**
     * \throws std::invalid_argument if len > this->len().
     */
    Buffer pop_front(int len);

    /**
     *
     */
    int len() const;

    void clear();

  private:		
    int m_capacity;
    int m_begin;
    int m_end;
		
    unsigned char* m_data;
  };
}

#endif

