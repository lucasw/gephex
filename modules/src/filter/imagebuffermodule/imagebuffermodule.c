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

#include "imagebuffermodule.h"

#if !defined(min)
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

static logT s_log;

struct CBuffer;

typedef void* (*ElemCreate)  (void);
typedef void  (*ElemDestroy) (void* elem);
typedef void  (*ElemAssign)  (void* dst, void* src);

/**
 * Returns an uninitialized CBuffer
 */
static struct CBuffer* cbuffer_alloc();

static void cbuffer_init(struct CBuffer* buf, int capacity,
			 ElemCreate, ElemAssign, ElemDestroy);

static void cbuffer_destroy(struct CBuffer* buf);

static void cbuffer_resize(struct CBuffer* buf, int new_capacity);

static void cbuffer_insert(struct CBuffer* buf, void* data);

static int cbuffer_num_elems(const struct CBuffer* buf);

static void* cbuffer_get_elem(const struct CBuffer* buf, int pos);


typedef struct _MyInstance {

 struct CBuffer* buffer;
 int old_capacity;

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

  my->old_capacity = 10;
  my->buffer = cbuffer_alloc();
  cbuffer_init(my->buffer, my->old_capacity,
	           (ElemCreate)framebuffer_newInstance,
			   (ElemAssign)framebuffer_assign,
			   (ElemDestroy)framebuffer_deleteInstance);
  
  return my;
}

void destruct(MyInstance* my)
{
  cbuffer_destroy(my->buffer);
  my->buffer = 0;
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  FrameBufferType* akt_buffer;
  int num_elems;
  int akt_elem;

  double pos = trim_double(inst->in_bpos->number, 0, 1);

  int capacity = trim_int(inst->in_bsize->number, 1, 250);

  int record = trim_bool(inst->in_record->number);

  if (capacity != my->old_capacity)
  {
	  cbuffer_resize(my->buffer, capacity);
	  my->old_capacity = capacity;
  }

  if (record)
	cbuffer_insert(my->buffer, inst->in_b);

  num_elems = cbuffer_num_elems(my->buffer);

  if (num_elems > 0)
  {

	akt_elem = (int) (pos * (num_elems-1));
	akt_buffer = cbuffer_get_elem(my->buffer, akt_elem);  

	framebuffer_assign(inst->out_r, akt_buffer);
  }
}

/*****************************************************************************/

struct CBuffer
{
	void** array;
	int capacity;
	int begin;
	int end;
	ElemCreate elem_create;
	ElemDestroy elem_destroy;
	ElemAssign elem_assign;
};

static struct CBuffer* cbuffer_alloc()
{
	struct CBuffer* buf = malloc(sizeof(struct CBuffer));
	buf->array = 0;
	buf->capacity = 0;
	buf->begin = buf->end = -1;
	buf->elem_assign = 0;
	buf->elem_create = 0;
	buf->elem_destroy = 0;

	return buf;
}

static void cbuffer_init(struct CBuffer* buf, int capacity,
						 ElemCreate create, ElemAssign assign, ElemDestroy destroy)
{	
	int size;	

	buf->elem_create = create;
	buf->elem_assign = assign;
	buf->elem_destroy = destroy;	

	buf->capacity = capacity;
	size = sizeof(void*) * capacity;
	buf->array = malloc(size);
	memset(buf->array, 0, size);

	buf->begin = 0;
	buf->end   = -1;
}

static void cbuffer_destroy(struct CBuffer* buf)
{		
	if (buf->array)
		free(buf->array);

	free(buf);
}


static void cbuffer_resize(struct CBuffer* buf, int new_capacity)
{
	int size = new_capacity * sizeof(void*);
	void** new_array = malloc(size);
	int new_begin = 0;
	int new_end;
    int common_capacity = min(new_capacity, buf->capacity);
    int i;
	int num_elems = cbuffer_num_elems(buf);

	memset(new_array, 0, size);

	if (num_elems == 0)
		new_end = -1;
	else
	{
		new_end = min(common_capacity, num_elems);
		
		for (i = 0; i < new_end; ++i)
		{
			new_array[i] = buf->array[(buf->begin + i) % buf->capacity];
		}
		
		if (new_capacity < num_elems)
		{
			for (i = new_capacity; i < num_elems; ++i)
				buf->elem_destroy(buf->array[(buf->begin + i) % buf->capacity]);
		}
	}
	free(buf->array);

	buf->array = new_array;
	buf->begin = new_begin;
	buf->end = new_end % new_capacity;
	buf->capacity = new_capacity;
}

static void cbuffer_insert(struct CBuffer* buf, void* data)
{
   void** assigned_elem = 0;

   if (buf->end == -1) // buffer still empty?
   {
	 assigned_elem = buf->array + buf->begin;
	 buf->end = (buf->begin + 1) % buf->capacity;
   }
   else if (buf->end == buf->begin) //buffer completely filled up
   {
	   assigned_elem = buf->array + buf->end;
	   buf->end = buf->begin = (buf->end + 1) % buf->capacity;
   }
   else // buffer partially filled
   {
	   assigned_elem = buf->array + buf->end;
	   buf->end = (buf->end + 1) % buf->capacity;
   }

   if (*assigned_elem  == 0)
	   *assigned_elem = buf->elem_create();

   buf->elem_assign(*assigned_elem, data);
}

static int cbuffer_num_elems(const struct CBuffer* buf)
{
	if (buf->end == -1)
		return 0;
	else if (buf->end > buf->begin)
		return buf->end - buf->begin;
	else
		return buf->capacity - (buf->begin - buf->end);
}

static void* cbuffer_get_elem(const struct CBuffer* buf, int pos)
{
	//TODO: check pos
	return buf->array[(buf->begin + pos) % buf->capacity];
}
