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

#include "chromakeymodule.h"

#include <math.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
#include "cpuinfo.h"
static int s_mmx_supported;
static int s_e3dnow_supported;
#endif

static logT s_log;

typedef void (*chroma_key_t)(uint_8 r, uint_8 g, uint_8 b, uint_8 tolerance,
                             uint_32* dst, const uint_32* fg,
                             const uint_32* bg, int size);

static void chroma_key(uint_8 r, uint_8 g, uint_8 b, uint_8 tolerance,
                       uint_32* dst, const uint_32* fg, const uint_32* bg,
                       int size);

static void chroma_key_smooth(uint_8 r, uint_8 g, uint_8 b, uint_8 tolerance,
                              uint_32* dst, const uint_32* fg,
                              const uint_32* bg, int size);

#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
extern void chroma_key_mmx(uint_8 r, uint_8 g, uint_8 b, uint_8 tolerance,
                           uint_32* dst, const uint_32* fg, const uint_32* bg,
                           int size);

extern void chroma_key_e3dnow(uint_8 r, uint_8 g, uint_8 b, uint_8 tolerance,
                              uint_32* dst, const uint_32* fg,
                              const uint_32* bg, int size);
#endif

typedef struct _MyInstance {

  // scaledFb is allocated lazily only when scaling is needed.
  // As soon as scaling is not performed anymore, it is freed.
  // So if scaling is constantly needed, there is no overhead
  // with allocating memory for scaledFb, and if no scaling is needed
  // there is no memory overhead.
  FrameBufferType* scaledFb;

  StringType mode;

  chroma_key_t chroma;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
  if (cpuinfo_has_cpuid())
    {
      s_mmx_supported    = cpuinfo_has_mmx();
      s_e3dnow_supported = cpuinfo_has_e3dnow();
    }
  else
    {
      s_mmx_supported    = 0;
      s_e3dnow_supported = 0;
    }

  if (s_mmx_supported)
    s_log(2, "found mmx support");
  else
    s_log(2, "no mmx support");

  if (s_e3dnow_supported)
    s_log(2, "found e3dnow support");
  else
    s_log(2, "no e3dnow support");
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
  {
    s_log(0, "Could not allocate memory for MyInstance struct\n");
    return 0;
  }

  my->scaledFb = 0;
  my->chroma   = 0;

  string_initInstance(&my->mode);

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFb != 0)
    framebuffer_deleteInstance(my->scaledFb);

  string_destroyInstance(&my->mode);
  free(my);
}

/**
 * Takes two framebuffertypes and scales them if they differ in size.
 * postcondition:
 *   *fb1 and *fb2 are arrays of the same size
 */
static void scale_framebuffers(const FrameBufferType* f1,
                               const FrameBufferType* f2,
                               FrameBufferType** scaled,
                               uint_32** fb1, uint_32** fb2,
                               int* xsize, int* ysize, int* did_scale)
{
  if (f1->xsize != f2->xsize
      || f1->ysize != f2->ysize)
    {
      // inputs have different sizes
      
      /*{
        char buffer[64];
        snprintf(buffer, sizeof(buffer),
        "In1 = %ix%i, In2 = %ix%i\n",
        f1->xsize, f1->ysize,
        f2->xsize, f2->ysize);

        s_log(2, buffer);
        }*/

      if (*scaled == 0)
        *scaled = framebuffer_newInstance();


      // indicate that we did scale this time
      *did_scale = 1;

      // scale the smaller input to the size of the other one
      if (f1->xsize * f1->ysize >
          f2->xsize * f2->ysize)
        {
          *fb1   = f1->framebuffer;		  
          *xsize = f1->xsize;
          *ysize = f1->ysize;

          framebuffer_scale(*scaled, f2, *xsize, *ysize);
          *fb2 = (*scaled)->framebuffer;
        }
      else
        {
          *fb2  = f2->framebuffer;
          *xsize = f2->xsize;
          *ysize = f2->ysize;

          framebuffer_scale(*scaled,f1, *xsize, *ysize);
          *fb1 = (*scaled)->framebuffer;
        }
    }
  else
    {
      // both inputs have the same size
      *did_scale = 0;
      *fb1 = f1->framebuffer;
      *fb2 = f2->framebuffer;
      *xsize = f1->xsize;
      *ysize = f1->ysize;		  
    }
}

static int do_patch(double tolerance)
{
  static const double EPS = 1.0 / 513.;

  if (tolerance < EPS)
    return 1;
  else if (tolerance > (1 - EPS))
    return 2;

  return 0;
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  double tolerance = trim_double(inst->in_tolerance->number, 0, 1);

  int patch = do_patch(tolerance);

  if (patch == 1)
    {
      neededInputs[in_bg]    = 0;
      neededInputs[in_color] = 0;
      neededInputs[in_mode]  = 0;
    }
  else if (patch == 2)
    {
      neededInputs[in_fg]    = 0;
      neededInputs[in_color] = 0;
      neededInputs[in_mode]  = 0;
    }
}

void patchLayout(Instance* inst, int out2in[])
{
  double tolerance = trim_double(inst->in_tolerance->number, 0, 1);
  
  int patch = do_patch(tolerance);

  if (patch == 1)
    out2in[out_r] = in_fg;
  else if (patch == 2)
    out2in[out_r] = in_bg;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  double tolerance = trim_double(inst->in_tolerance->number, 0, 1);

  uint_32* fg = 0;
  uint_32* bg = 0;
  int didScale = 0;

  int xsize = 0, ysize = 0;

  double r;
  double g;
  double b;

  if (do_patch(tolerance))
    return;

  r = trim_double(inst->in_color->r, 0, 1);
  g = trim_double(inst->in_color->g, 0, 1);
  b = trim_double(inst->in_color->b, 0, 1);

  if (strcmp(my->mode.text, inst->in_mode->text) != 0)
    {
      string_assign(&my->mode, inst->in_mode);

      if (strcmp(my->mode.text, "smooth") == 0)
	{
	  s_log(2, "Using smooth algorithm");
	  my->chroma = chroma_key_smooth;
	}
      else
	{
	  char buffer[128];

          if (strcmp(my->mode.text, "default") == 0)
            s_log(2, "Using default algorithm");
          else
            {
              snprintf(buffer, sizeof(buffer),
                       "Unsupported chroma algo: '%s', "
                       "using 'default' instead",
                       my->mode.text);

              s_log(0, buffer);
            }
#if defined(CPU_I386) && defined(OPT_INCLUDE_MMX)
          if (s_e3dnow_supported)
            my->chroma = chroma_key_e3dnow;
          else if (s_mmx_supported)
            my->chroma = chroma_key_mmx;
          else
#endif
            my->chroma = chroma_key;

	}
    }

  scale_framebuffers(inst->in_fg, inst->in_bg,
                     &my->scaledFb, &fg, &bg,
                     &xsize, &ysize, &didScale);
      
  // scale output framebuffer to the size of the inputs
  {
    FrameBufferAttributes attribs;

    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attribs);
  }

  my->chroma(color_comp_to_byte(r),
             color_comp_to_byte(g),
             color_comp_to_byte(b),
             color_comp_to_byte(tolerance),
             inst->out_r->framebuffer,
             fg, bg, xsize * ysize);

  // delete scaled framebuffer if we didn't need it this time
  if (didScale == 0 && my->scaledFb != 0)
    {
      framebuffer_deleteInstance(my->scaledFb);
      my->scaledFb = 0;
    }  
}

//---------------------------------------------------------------------------

__inline static int color_matches(uint_32 c, uint_8 r, uint_8 g, uint_8 b,
                                   uint_8 tolerance)
{
  uint_8* cc = (uint_8*) &c;

  return (abs(cc[0] - b) < tolerance) &&
    (abs(cc[1] - g) < tolerance) &&
    (abs(cc[2] - r) < tolerance);
}

static void chroma_key(uint_8 rr, uint_8 gg, uint_8 bb, uint_8 tt,
                       uint_32* dst, const uint_32* fg, const uint_32* bg,
                       int size)
{
  uint_32* idst      = dst;
  const uint_32* ifg = fg;
  const uint_32* ibg = bg;

  int i;

  for (i = size-1; i >= 0; --i, ++idst, ++ifg, ++ibg)
    {
      *idst = color_matches(*ifg, rr, gg, bb, tt) ? *ibg : *ifg;
    }  
}

static __inline void MULT_PIX(uint_32* dst, uint_32 p, int f)
{
  uint_8* pp = (uint_8*) &p;
  dst[0] = pp[0] * f;
  dst[1] = pp[1] * f;
  dst[2] = pp[2] * f;
}

static __inline void ADD_PIX(uint_32* dst, uint_32* src)
{
  dst[0] += src[0];
  dst[1] += src[1];
  dst[2] += src[2];
}

static __inline void ROUND_PIX(uint_32* dst, uint_32* p)
{
  uint_8* dd = (uint_8*) dst;

  dd[0] = (p[0] + 255) >> 8;
  dd[1] = (p[1] + 255) >> 8;
  dd[2] = (p[2] + 255) >> 8;
}

static __inline  int max2(int a, int b)
{
  return (a < b) ? b : a;
}

static __inline  int max3(int a, int b, int c)
{
  return max2(max2(a, b), c);
}

static void chroma_key_smooth(uint_8 rr, uint_8 gg, uint_8 bb, uint_8 tt,
                              uint_32* dst, const uint_32* fg,
                              const uint_32* bg, int size)
{
  uint_32* idst      = dst;
  const uint_32* ifg = fg;
  const uint_32* ibg = bg;
  int i;

  for (i = size-1; i >= 0; --i, ++idst, ++ifg, ++ibg)
    {
      uint_8* cc = (uint_8*) ifg;

      int eb = abs(cc[0] - bb);
      int eg = abs(cc[1] - gg);
      int er = abs(cc[2] - rr);

      if (eb < tt && eg < tt && er < tt)
        {
          int em = max3(eb, eg, er) >> 3;
          uint_32 tmp_fg[4];
          uint_32 tmp_bg[4];

          MULT_PIX(tmp_fg, *ifg, em);
          MULT_PIX(tmp_bg, *ibg, 255 - em);
          ADD_PIX(tmp_fg, tmp_bg);
          ROUND_PIX(idst, tmp_fg);
        }
      else
        *idst = *ifg;
    }  
}

//---------------------------------------------------------------------------
