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

#include "fpsmodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <sys/timeb.h>
#elif defined(OS_POSIX)
#include <sys/time.h>
#endif

#define HISTORY_SIZE 10

typedef struct _MyInstance {
 unsigned long last_time;
 unsigned long last_diffs[HISTORY_SIZE];
 int begin;
 int end;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

static unsigned long get_time();
MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->last_time = get_time();
  my->begin = 0;  
  my->end = 0;

  return my;
}

void destruct(MyInstance* my)
{  
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  unsigned long time, diff;
  int i, sum, count;

  time = get_time();
  diff = time - my->last_time;
  my->last_time = time;

  my->last_diffs[my->end] = diff;

  my->end = (my->end + 1) % HISTORY_SIZE;  

  if (my->begin == my->end)
	  my->begin = (my->begin + 1) % HISTORY_SIZE;

  sum = 0;
  count = 0;
  for (i = my->begin; i != my->end; i = (i+1) % HISTORY_SIZE)
  {
	  sum += my->last_diffs[i];
	  ++count;
  }

  if (sum != 0)
	inst->out_fps->number = (unsigned int) (1000. * count / sum);
  else
	inst->out_fps->number = 0;

}

static unsigned long get_time()
{
  unsigned long time;

#if defined(OS_WIN32)

  struct _timeb timebuffer;
  _ftime( &timebuffer );
  time = timebuffer.time*1000 + timebuffer.millitm;

#elif defined(OS_POSIX)

  struct timeval tv;
  gettimeofday(&tv, 0);
  time = tv.tv_sec*1000 + tv.tv_usec/1000;

#endif

  return time;
}
