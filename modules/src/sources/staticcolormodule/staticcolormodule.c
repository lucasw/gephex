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

#include "staticcolormodule.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
#include "cpuinfo.h"
static int s_mmx_supported = 0;
#endif

static logT s_log;

typedef struct _MyInstance {

  uint_32 old_color;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    s_mmx_supported = cpuinfo_has_mmx();
  else
    s_mmx_supported = 0;

  if (s_mmx_supported)
    s_log(2, "found mmx support");
  else
    s_log(2, "no mmx support");
#endif

  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  my->old_color = 12345;
  return my;
}

void destruct(MyInstance* my)
{
  free(my);
}

static void fill(uint_32* fb, int size, uint_32 color);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
extern void fill_mmx(uint_32* fb, int size, uint_32 color);
#endif

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  unsigned char colora[4];
  uint_32 color;
  int size;

  FrameBufferAttributes attribs;

  attribs.xsize = trim_int(inst->in_xsize->number, 0, 4096);
  attribs.ysize = trim_int(inst->in_ysize->number, 0, 4096);
  framebuffer_changeAttributes(inst->out_r, &attribs);
  
  size = inst->out_r->xsize * inst->out_r->ysize;
  
  colora[0] = color_comp_to_byte(inst->in_col->b);
  colora[1] = color_comp_to_byte(inst->in_col->g);
  colora[2] = color_comp_to_byte(inst->in_col->r);
  colora[3] = 0; //TODO: alpha?

  color = *((uint_32*) colora);

  if (my->old_color == color)
    return;
  else
    my->old_color = color;
  
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (s_mmx_supported)
    {
      fill_mmx(inst->out_r->framebuffer, size, color);
    }
  else
#endif
    {
      fill(inst->out_r->framebuffer, size, color);
    }
}

/*****************************************************************************/

static void fill(uint_32* fb, int size, uint_32 color)
{
  uint_32* pointer = 0;
  for (pointer = fb + size - 1; pointer >= fb; pointer--)
    {
      *pointer = color;
    }
}

/*****************************************************************************/
