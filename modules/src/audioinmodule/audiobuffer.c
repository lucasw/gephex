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

#include "audiobuffer.h"

#include <stdio.h>
#include <assert.h>

#include <windows.h>

// ---------------------------------------------------------------------------

static int init_buffer_block(HWAVEIN wavein, WAVEHDR* hdr, int block_size)
{
	MMRESULT res;

	memset(hdr, 0, sizeof(*hdr));
	hdr->lpData = malloc(block_size);
	hdr->dwBufferLength = block_size;	
	hdr->dwFlags = 0;
	res = waveInPrepareHeader(wavein, hdr, sizeof(*hdr));
	if (res != MMSYSERR_NOERROR)
	{
		char error_msg[128];
		waveInGetErrorText(res, error_msg, sizeof(error_msg));
		printf("init_buffer_block failed: %s!\n", error_msg);
		return 0;
	}
	return 1;
}

static int deinit_buffer_block(HWAVEIN wavein, WAVEHDR* hdr)
{
	MMRESULT res;
	res = waveInUnprepareHeader(wavein, hdr, sizeof(*hdr));
	if (res != MMSYSERR_NOERROR)
	{
		char error_msg[128];
		waveInGetErrorText(res, error_msg, sizeof(error_msg));
		printf("init_buffer_block failed: %s!\n", error_msg);
		return 0;
	}
	free(hdr->lpData);
	return 1;
}

// ---------------------------------------------------------------------------

struct ab_queue_node
{
	struct ab_queue_node* next;
	WAVEHDR hdr;	
};

struct ab_queue
{
	int len;
	HWAVEIN wavein;
	struct ab_queue_node* first;
};

static struct ab_queue* ab_queue_create(int len, int block_size, HWAVEIN wavein)
{
	struct ab_queue* queue = malloc(sizeof(*queue));
	struct ab_queue_node* last_node;
	struct ab_queue_node* current_node;

	int i;

	queue->len = len;
	queue->wavein = wavein;
	
	last_node = 0;
	for (i = 0; i < len; ++i)
	{
		MMRESULT res;

		current_node = malloc(sizeof(*current_node));

		init_buffer_block(wavein, &current_node->hdr, block_size);
		res = waveInAddBuffer(wavein, &current_node->hdr, sizeof(current_node->hdr));
		if (res != MMSYSERR_NOERROR)
		{
			char error_msg[128];
			waveInGetErrorText(res, error_msg, sizeof(error_msg));
			printf("waveInAddBuffer failed: %s!\n", error_msg);
			return 0;
		}

		if (last_node != 0)
			last_node->next = current_node;
		else {
			queue->first = current_node;			
		}

		last_node = current_node;
	}
	
	last_node->next = queue->first;

	return queue;
}

static void ab_queue_destroy(struct ab_queue* queue)
{
	int num_nodes = 0;
	struct ab_queue_node* current;

	current = queue->first;
	do 
	{
		struct ab_queue_node* tmp;
				
		deinit_buffer_block(queue->wavein, &current->hdr);
		
		tmp = current;
		current = current->next;
		free(tmp);
		++num_nodes;
	} while (current != queue->first);

	assert(num_nodes = queue->len);
	free(queue);
}

static WAVEHDR* ab_queue_top(struct ab_queue* self) {
	return &self->first->hdr;
}

static void ab_queue_next(struct ab_queue* self) {
	self->first = self->first->next;
}
// ---------------------------------------------------------------------------

struct audio_buffer
{
	int block_size;
	int num_blocks;

	HWAVEIN wavein;
	struct ab_queue* queue;
};


struct audio_buffer* ab_create(void* wavein, int block_size, int num_blocks)
{
	struct audio_buffer* buf = malloc(sizeof(*buf));
	buf->block_size = block_size;
	buf->num_blocks = num_blocks;
	buf->wavein = wavein;

	buf->queue = ab_queue_create(num_blocks, block_size, wavein);

	return buf;
}

void ab_destroy(struct audio_buffer* buf) {
	ab_queue_destroy(buf->queue);

	free(buf);
}

int ab_block_ready(const struct audio_buffer* buf) {
	const WAVEHDR* hdr = ab_queue_top(buf->queue);
	return (hdr->dwFlags & WHDR_DONE);
}


int ab_get_block(struct audio_buffer* buf, unsigned char* data, int data_len)
{
	WAVEHDR* hdr;
	MMRESULT res;
	int min_len;
	if (!ab_block_ready(buf))
		return 0;

	hdr = ab_queue_top(buf->queue);
	min_len = min(data_len, (int)hdr->dwBytesRecorded);
	memcpy(data, hdr->lpData, min_len);

	//TODO: is it necessary to unprepare and prepare the header here?
	res = waveInAddBuffer(buf->wavein, hdr, sizeof(*hdr));
	if (res != MMSYSERR_NOERROR)
	{
		char error_msg[128];
		waveInGetErrorText(res, error_msg, sizeof(error_msg));
		printf("waveInAddBuffer failed: %s!\n", error_msg);
		return 0;
	}

	ab_queue_next(buf->queue);

	return min_len;
}

// ---------------------------------------------------------------------------