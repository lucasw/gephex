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

#ifndef INCLUDED_AUDIO_BUFFER_H
#define INCLUDED_AUDIO_BUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif

struct audio_buffer;

/**
 * wavein must already be opened.
 * The audio_buffer is *not* responsible for starting/stopping
 * wavein.
 *
 * To use it, 
 *    - first open the waveIn device
 *    - then create the audio buffer
 *    - use it (you can call waveInStart/Stop here)
 *    - reset the waveIn device
 *    - destroy the audio buffer
 *
 * It's important not to destroy the audio buffer earlier!
 * If you don't want to lose data, you should not call waveInStart before
 * you create the buffer.
 *
 * IMPORTANT: the wavein device *must* be opened for polling,
 * i.e. with 0 as callback function and without any callback flags.
 */
struct audio_buffer* ab_create(void* wavein, int block_size, int num_blocks);

void ab_destroy(struct audio_buffer*);

/**
 * polls the wavein device for full blocks.
 */
int ab_block_ready(const struct audio_buffer*);

/**
 * returns at most buf->block_size bytes.
 */
int ab_get_block(struct audio_buffer* buf, unsigned char* data, int data_len);
#ifdef __cplusplus
}
#endif
#endif
