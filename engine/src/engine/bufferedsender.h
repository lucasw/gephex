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

#ifndef INCLUDED_BUFFERED_SENDER_H
#define INCLUDED_BUFFERED_SENDER_H

#include <memory>

#include "isender.h"

namespace utils
{
	class Buffer;
	class CircularBuffer;
}

/**
 * The BufferedSender can be disabled, in which case it ignores all data
 * that is sent or enabled, in which case it stores all data.
 *
 * When created it is disabled.
 */
class BufferedSender : public net::ISender
{
public:
	BufferedSender();
	virtual ~BufferedSender();

	void disable();
	void enable();

	int send(const utils::Buffer& buf);

	/**
	 *
	 */
	int len() const;

	/**
	 *
	 */
	utils::Buffer consume(int num_bytes);

private:
	std::auto_ptr<utils::CircularBuffer> m_buffer;
    bool m_enabled;
};

#endif
