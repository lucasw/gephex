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
    {
      s_mmx_supported = cpuinfo_has_mmx();
      s_log(2, "found mmx support");
    }
  else
    {
      s_mmx_supported = 0;
      s_log(2, "no mmx support");
    }
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
static void fill_mmx(uint_32* fb, int size, uint_32 color);
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
  
  colora[0] = (unsigned char)(inst->in_col->b*255);
  colora[1] = (unsigned char)(inst->in_col->g*255);
  colora[2] = (unsigned char)(inst->in_col->r*255);
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

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
static void fill_mmx(uint_32* fb, int size, uint_32 color_)
{
  unsigned char color[8];
  unsigned char* dst = (unsigned char*) fb;
  int size_ = size * 4;

  memcpy(color, &color_, sizeof(color_));
  memcpy(color+4, &color_, sizeof(color_));

#if defined(COMP_VC)
  _asm
  {
      mov edi, dst
	  mov eax, size_
	  shr eax, 5
	  cmp eax, 0
	  jz stat_mmx_end
	  movq mm1, [color]
loop_1:
      movq [edi], mm1
	  movq [edi+8], mm1
	  movq [edi+16], mm1
	  movq [edi+24], mm1
	  add edi, 32
	  dec eax
	  jnz loop_1
	  emms
stat_mmx_end:
  }
#elif defined(COMP_GCC)
  {
    int d0, d1;
    __asm__ __volatile__ (
      "shrl $5, %%eax              \n\t"
      "cmpl $0, %%eax              \n\t"
      "jz 2f                       \n\t"
      "movq (%4), %%mm1            \n\t"
      "1:                          \n\t"
      "  movq %%mm1,   (%%edi)     \n\t"
      "  movq %%mm1,  8(%%edi)     \n\t"
      "  movq %%mm1, 16(%%edi)     \n\t"
      "  movq %%mm1, 24(%%edi)     \n\t"
      "  addl $32, %%edi           \n\t"
      "  decl %%eax                \n\t"
      "jnz 1b                      \n\t"
      "emms                        \n\t"
      "2:                          \n\t"
      : "=&D"(d0), "=&a"(d1)
      : "0"(dst), "1"(size_), "r"(color)
      : "memory"
      );
  }
#else
#error "Not implemented for this compiler!"
#endif

  {
    int rest = size & 0x07;
    if (rest != 0)
      {
        fill(fb+size-rest, rest, color_);
      }
  }
}
#endif
