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

#include "gradnormmodule.h"

#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>

#if !defined(_MSC_VER) || (_MSC_VER > 1200)
using std::min;
#include <stdint.h>
#else
#define min(a, b) ((a) < (b) ? (a) : (b))
#include "basic_types.h"
typedef uint_32 uint32_t;
typedef uint_8  uint8_t;
#endif

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
#include "cpuinfo.h"
static int s_3dnow_supported = 0;
static int s_e3dnow_supported = 0;
#endif

static logT s_log;

//---------------------------------------------------------------------------

static void sobel(int xsize, int ysize,
                  const uint_32* fb,
                  uint_32* outfb,
                  float scale);

static void roberts_cross(int xsize, int ysize,
                          const uint_32* fb,
                          uint_32* outfb,
                          float scale);


#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)

extern "C"
{
void roberts_cross_e3dnow(int_32 xsize, int_32 ysize,
                          const uint_32* fb,
                          uint_32* outfb,
                          float scale);
}


static void sobel_3dnow(int xsize, int ysize,
                        const uint_32* fb,
                        uint_32* outfb,
                        float scale);

static float sqrt_3dnow(float a)
{
  float result;
#if defined(COMP_GCC)
  __asm__
    (
     "movd      %1, %%mm0                \n"
     "pfrsqrt   %%mm0, %%mm1             \n"
     "punpckldq %%mm0, %%mm0             \n"
     "pfmul     %%mm1, %%mm0             \n"
     "movd      %%mm0, %0                \n"
     "femms                              \n"
     : "=m"(result)
     : "m" (a)
     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)"
     );
#elif defined(COMP_VC)
  __asm
  {
	  movd  mm0, a

	  _emit 0x0f
	  _emit 0x0f
	  _emit 0xc8
	  _emit 0x97  // pfrsqrt mm1, mm0

	  punpckldq mm0, mm0

	  _emit 0x0f
	  _emit 0x0f
	  _emit 0xc1
	  _emit 0xb4  // pfmul mm0, mm1

	  movd  result, mm0

	  _emit 0x0f
	  _emit 0x0e // femms	  
  }

#else
  result = sqrtf(a);
#endif

  return result;
}
#endif

static inline uint32_t grey(const uint32_t& rgb)
{
  const uint8_t* mask = reinterpret_cast<const uint8_t*>(&rgb);
  return (mask[0] + mask[1] + mask[2]);
}

//---------------------------------------------------------------------------

typedef void (*edge_algo_t)(int, int,
                            const uint_32*,
                            uint_32*,
                            float);

typedef struct _MyInstance {

  std::string* algo_name;

  edge_algo_t algo;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    {
      s_3dnow_supported = cpuinfo_has_3dnow();
      s_e3dnow_supported = cpuinfo_has_e3dnow();

      if (s_e3dnow_supported)
        s_log(2, "found e3dnow support");
      else if (s_3dnow_supported)
        s_log(2, "found 3dnow support");
      else
        s_log(2, "3dnow support *not* found");
    }
  else
    {
      s_3dnow_supported = 0;
      s_e3dnow_supported = 0;
      s_log(2, "3dnow support *not* found");
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

  if (my == 0)
    return 0;

  my->algo_name = new std::string("");
  my->algo = 0;

  return my;
}

void destruct(MyInstance* my)
{
  delete my->algo_name;
  my->algo_name = 0;
  my->algo = 0;

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  std::string algo_name(inst->in_algo->text);

  if (my->algo == 0 || algo_name != *my->algo_name)
    {
      *my->algo_name = algo_name;
      if (algo_name == "sobel")
        {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
          if (s_3dnow_supported)
            my->algo = sobel_3dnow;
          else
#endif
          my->algo = sobel;
        }
      else if (algo_name == "roberts-cross")
        {
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
          if (s_e3dnow_supported)
            my->algo = roberts_cross_e3dnow;
          else
#endif
          my->algo = roberts_cross;
        }
      else
        {
          char buffer[256];
          snprintf(buffer, sizeof(buffer),
                   "Invalid Algorithm: '%s', using 'roberts-cross'",
                   algo_name.c_str());
          s_log(1, buffer);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
          if (s_e3dnow_supported)
            my->algo = roberts_cross_e3dnow;
          else
#endif
          my->algo = roberts_cross;
        }
    }

  assert(my->algo != 0);

  FrameBufferAttributes attribs;
  framebuffer_getAttributes(inst->in_b, &attribs);
  framebuffer_changeAttributes(inst->out_r, &attribs);

  int xsize         = inst->in_b->xsize;
  int ysize         = inst->in_b->ysize;
  
  double scale      = trim_double(inst->in_scale->number, 0.0, 1.0)*3;
  const uint_32* fb = inst->in_b->framebuffer;
  uint_32* outfb    = inst->out_r->framebuffer;

  if (xsize <= 3 || ysize <= 3)
    {
      memset(outfb, 0, xsize*ysize*4);
      return;
    }

  my->algo(xsize, ysize, fb, outfb, scale);
}

static void roberts_cross(int xsize, int ysize,
                          const uint_32* fb,
                          uint_32* outfb,
                          float scale)
{
  assert(xsize > 3);
  assert(ysize > 3);

  const uint_32* ptr = fb + xsize + 1;
  uint_32* out_ptr   = outfb+xsize+1;

  float sc = scale;

  for (int y = ysize-3; y >= 0; --y, out_ptr += 2, ptr += 2)
    for (int x = xsize-3; x >= 0; --x, ++out_ptr, ++ptr)
      {
        int a1 = grey(ptr[-xsize-1]);
        int a2 = grey(ptr[0]);
        int a3 = grey(ptr[-xsize]);
        int a4 = grey(ptr[-1]);

        int gradx = abs(a1-a2);
        int grady = abs(a3-a4);

        float gn = gradx + grady;
	
        uint8_t vd = static_cast<uint8_t>(min(255.0f, gn*sc));
	    
        uint8_t* out = reinterpret_cast<uint8_t*>(out_ptr);
        *out = *(out+1) = *(out+2) = vd; 
      }
}



static void sobel(int xsize, int ysize,
                      const uint_32* fb,
                      uint_32* outfb,
                      float scale)
{
  assert(xsize > 3);
  assert(ysize > 3);
  int index = 1 + xsize;
  float sc = scale / 5.0;

  for (int y = ysize-3; y >= 0; --y, index += 2)
    for (int x = xsize-3; x >= 0; --x, ++index)
      {
        int a1 = grey(fb[index - 1 - xsize]);
        int a2 = grey(fb[index     - xsize]);
        int a3 = grey(fb[index + 1 - xsize]);
        int a4 = grey(fb[index - 1        ]);
        int a6 = grey(fb[index + 1        ]);
        int a7 = grey(fb[index - 1 + xsize]);
        int a8 = grey(fb[index     + xsize]);
        int a9 = grey(fb[index + 1 + xsize]);

        // derivate in the two directions with the sobel operator
        int gradx = (-a1+a3-2*a4+2*a6-a7+a9);
        int grady = (-a1-2*a2-a3+a7+2*a8+a9);

        // norm
        //        float gn = sqrtf(gradx*gradx+grady*grady);
        float gn = abs(gradx) + abs(grady);
	
        float vd = min(255.0f, gn*sc);
	    
        uint8_t* out = reinterpret_cast<uint8_t*>(outfb + index);
        *out = *(out+1) = *(out+2) = *(out+3) = static_cast<uint8_t>(vd); 
      }
}


#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)

static void sobel_3dnow(int xsize, int ysize,
                            const uint_32* fb,
                            uint_32* outfb,
                            float scale)
{
  assert(xsize > 3);
  assert(ysize > 3);
  int index = 1 + xsize;

  float sc = scale / 5.0;

  for (int y = ysize-3; y >= 0; --y, index += 2)
    for (int x = xsize-3; x >= 0; --x, ++index)
      {
        int a1 = grey(fb[index - 1 - xsize]);
        int a2 = grey(fb[index     - xsize]);
        int a3 = grey(fb[index + 1 - xsize]);
        int a4 = grey(fb[index - 1        ]);
        int a6 = grey(fb[index + 1        ]);
        int a7 = grey(fb[index - 1 + xsize]);
        int a8 = grey(fb[index     + xsize]);
        int a9 = grey(fb[index + 1 + xsize]);

        // derivate in the two directions with the sobel operator
        int gradx = (-a1+a3-2*a4+2*a6-a7+a9);
        int grady = (-a1-2*a2-a3+a7+2*a8+a9);

        // norm
        float gn = sqrt_3dnow(gradx*gradx+grady*grady);
        //float gn = abs(gradx) + abs(grady);
	
        float vd = min(255.0f, gn*sc);
	    
        uint8_t* out = reinterpret_cast<uint8_t*>(outfb + index);
        *out = *(out+1) = *(out+2) = *(out+3) = static_cast<uint8_t>(vd); 
      }
}


#endif
