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

#include "audioaddmodule.h"

#include <math.h>

static logT s_log;

#define CAPACITY (1024*32)

#ifdef min
#undef min
#endif
int min(int a, int b) {
	return (a < b) ? a : b;
}


typedef struct _MyInstance {

  double* left_buffer;
  double* right_buffer;

  int buffer_capacity;
  int left_pos;
  int right_pos;

  int flush;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->buffer_capacity = CAPACITY;
  my->left_pos        = 0;
  my->right_pos       = 0;
  my->left_buffer     = malloc(sizeof(double) * my->buffer_capacity);
  my->right_buffer    = malloc(sizeof(double) * my->buffer_capacity);

  my->flush           = 0;

  return my;
}

void destruct(MyInstance* my)
{
  free(my->left_buffer);
  free(my->right_buffer);

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  
  int left_len  = min(my->buffer_capacity - my->left_pos, inst->in_lhs->len);
  int right_len = min(my->buffer_capacity - my->right_pos, inst->in_rhs->len);
  int thr       = trim_int(inst->in_thr->number, 0, 4096);
  double w_l    = trim_double(inst->in_w_lhs->number, 0, 1);
  double w_r    = trim_double(inst->in_w_rhs->number, 0, 1);
  int flush     = trim_bool(inst->in_flush->number);

  if (inst->in_lhs->sample_rate != inst->in_rhs->sample_rate ||
	  inst->in_lhs->channels != inst->in_rhs->channels)
  {
	s_log(0, "Format of audio streams different");
	inst->out_r->len = 0;
	return;
  }

  if (flush != my->flush) {
    my->left_pos = my->right_pos = 0;
    my->flush = flush;
  }

  memcpy(my->left_buffer + my->left_pos, inst->in_lhs->samples, left_len*sizeof(double));
  memcpy(my->right_buffer + my->right_pos, inst->in_rhs->samples, right_len*sizeof(double));

  my->left_pos  += left_len;
  my->right_pos += right_len;

  //  printf("left = %i\t\t\t\tright = %i\n", my->left_pos, my->right_pos);

  inst->out_r->sample_rate = inst->in_lhs->sample_rate;

  if (my->left_pos > thr && my->right_pos > thr)
  {
	int	common_len = min(my->left_pos, my->right_pos);
	int i;

	audio_resize(inst->out_r, common_len);
	inst->out_r->len = common_len;

	for (i = 0; i < common_len; ++i) {
		double v = w_l * my->left_buffer[i] + w_r * my->right_buffer[i];
		if (v < -1)
			v = -1;
		else if (v > 1)
			v = 1;

		inst->out_r->samples[i] = v;		 
	}
	/*if (my->left_pos < my->right_pos)
		for (i = common_len; i < my->right_pos; ++i)
			inst->out_r->samples[i] = my->right_buffer[i];
	else
		for (i = common_len; i < my->left_pos; ++i)
			inst->out_r->samples[i] = my->left_buffer[i];*/

	memmove(my->left_buffer,  my->left_buffer  + common_len, (my->left_pos - common_len)*sizeof(double));
	memmove(my->right_buffer, my->right_buffer + common_len, (my->right_pos - common_len)*sizeof(double));
	my->left_pos  -= common_len;
	my->right_pos -= common_len;

	//printf("adding %i samples\n", common_len);
  }
  else {
	  inst->out_r->len = 0;
  }

}

