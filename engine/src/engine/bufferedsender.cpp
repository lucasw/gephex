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

#include "bufferedsender.h"

#include "utils/buffer.h"
#include "utils/circularbuffer.h"

BufferedSender::BufferedSender()
: m_buffer(new utils::CircularBuffer()), m_enabled(false)
{
   
}

BufferedSender::~BufferedSender()
{
}

void BufferedSender::disable()
{
  m_buffer->clear();
  m_enabled = false;
}

void BufferedSender::enable()
{
	m_enabled = true;
}

int BufferedSender::send(const utils::Buffer& buf)
{
	if (m_enabled)
	    m_buffer->push_back(buf);

	return buf.getLen();
}

/**
 *
 */
int BufferedSender::len() const
{
	return m_buffer->len();
}

/**
 *
 */
utils::Buffer BufferedSender::consume(int num_bytes)
{
	return m_buffer->pop_front(num_bytes);
}
