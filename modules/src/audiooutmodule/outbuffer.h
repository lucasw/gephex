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

#ifndef INCLUDED_OUTBUFFER_H
#define INCLUDED_OUTBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

struct out_buffer;

/**
 * handle must already be opened.
 * The out_buffer is *not* responsible for starting/stopping
 * waveout.
 *
 * To use it, 
 *    - first open the waveOut device
 *    - then create the outbuffer
 *    - use it (you can call waveOutStop,... here)
 *    - reset the waveOut device
 *    - destroy the outbuffer
 *
 * It's important not to destroy the outbuffer earlier!
 *
 * IMPORTANT: the wavout device *must* be opened for polling,
 * i.e. with 0 as callback function and without any callback flags.
 */
struct out_buffer* outb_create(void* handle, int bytes_per_buffer, int num_buffers);

void outb_destroy(struct out_buffer* buf);

/**
 * Returns number of written bytes. Negative value indicates an error.
 */
int outb_write(struct out_buffer* buf, const unsigned char* data, int num_bytes,
			   char* error_text, int text_len);

#ifdef __cplusplus
}
#endif

#endif
