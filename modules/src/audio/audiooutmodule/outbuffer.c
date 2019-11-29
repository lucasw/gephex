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

#include "outbuffer.h"

#include <windows.h>
#include <stdio.h>

//--------------------------------------------------------------------------

struct out_buffer {
	HWAVEOUT handle;
	int block_size;
	int num_blocks;
	WAVEHDR* headers;
};

//--------------------------------------------------------------------------

static int outb_init_block(HWAVEOUT handle, WAVEHDR* hdr, int block_size)
{
	MMRESULT res;

	memset(hdr, 0, sizeof(*hdr));
	hdr->dwBufferLength = block_size;	
	hdr->dwFlags        = 0;
	hdr->lpData         = malloc(block_size);
	if (hdr->lpData == 0)
	{
		printf("Could not allocate memory for audio block in " 
			   "audiooutmodule::outbuffer::outb_init_block()\n");
		return 0;
	}

	res = waveOutPrepareHeader(handle, hdr, sizeof(*hdr));
	if (res != MMSYSERR_NOERROR)
	{
		char error_msg[128];
		waveInGetErrorText(res, error_msg, sizeof(error_msg));
		printf("outb_init_block failed: %s!\n", error_msg);
		return 0;
	}
	return 1;
}

static int outb_deinit_block(HWAVEOUT handle, WAVEHDR* hdr)
{
	MMRESULT res;
	res = waveOutUnprepareHeader(handle, hdr, sizeof(*hdr));
	if (res != MMSYSERR_NOERROR)
	{
		char error_msg[128];
		waveOutGetErrorText(res, error_msg, sizeof(error_msg));
		printf("outb_deinit_block failed: %s!\n", error_msg);
		return 0;
	}
	free(hdr->lpData);
	return 1;
}

struct out_buffer* outb_create(HWAVEOUT handle, int bytes_per_buffer, int num_buffers)
{
	struct out_buffer* buf = malloc(sizeof(*buf));
	int i;

	if (buf == 0)
	{
		printf("Could not allocate memory for buffer in " 
			   "audiooutmodule::outbuffer::outb_create()\n");
		return 0;
	}

	buf->handle     = handle;
	buf->block_size = bytes_per_buffer;
	buf->num_blocks = num_buffers;
	buf->headers    = malloc(num_buffers*sizeof(WAVEHDR));

	if (buf->headers == 0)
	{
		printf("Could not allocate memory for audio headers in " 
			   "audiooutmodule::outbuffer::outb_create()\n");
		free(buf);
		return 0;
	}

	for (i = 0; i < num_buffers; ++i)
	{
		int result;
		result = outb_init_block(handle, buf->headers + i, bytes_per_buffer);
		if (result == 0)
		{
			printf("Could not init block #%i in " 
			   "audiooutmodule::outbuffer::outb_create() - leaking memory\n", i);

			//TOCHECK: don't deinit already initialized blocks, because
			// this could produce errors again. Instead just leak them.
			free(buf->headers);
			free(buf);
			return 0;
		}
	}

	return buf;
}

void outb_destroy(struct out_buffer* buf)
{
    int i;

	for (i = 0; i < buf->num_blocks; ++i)	
		outb_deinit_block(buf->handle, buf->headers + i);

	free(buf->headers);
	free(buf);
}

static int outb_get_next_free_block(WAVEHDR* headers, int num_blocks, int start_index)
{
	int i = start_index;
	while (i < num_blocks) {		
		if (!(headers[i].dwFlags & WHDR_INQUEUE))
			return i;

		++i;
	}
	return -1;
}

int outb_write(struct out_buffer* buf, const unsigned char* data, int num_bytes,
			   char* error_text, int text_len)
{
	int index = -1;
	WAVEHDR* header;
	int len;
	MMRESULT res;
	int bytes_written = 0;

	while (bytes_written < num_bytes) 
	{
		// get a free buffer block
		index = outb_get_next_free_block(buf->headers, buf->num_blocks, index+1);
		if (index == -1)
			return bytes_written; // no free buffer found => return
		header = buf->headers + index;
		
		// copy data to the buffer
		len                    = min(buf->block_size, num_bytes - bytes_written);
		header->dwBufferLength = len;
		header->dwFlags        = WHDR_PREPARED;
		memcpy(header->lpData, data + bytes_written, len);

		// write data out
		res = waveOutWrite(buf->handle, header, sizeof(*header));
		if (res != MMSYSERR_NOERROR)
		{
			char error_msg[128];
			waveInGetErrorText(res, error_msg, sizeof(error_msg));
			_snprintf(error_text, text_len, "waveOutWrite failed: %s!", error_msg);
			return -1;
		}

		bytes_written += len;
	}

	return num_bytes;
}

//--------------------------------------------------------------------------