/* Displacement Module
  Copyright (C) 2004 Martin Bayer, Georg Seidel, Philipp Promesberger
  This file is part of GePhex (http://www.gephex.org).

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
*/

#include <math.h>

#include "dplmodule.h"

#if defined _MSC_VER
#define M_PI 3.14159265358979323846
#else
#define min(a, b) ( (a) < (b) ? (a) : (b) )
#define max(a, b) ( (a) > (b) ? (a) : (b) )
#endif

static logT s_log;

typedef struct _MyInstance {

  FrameBufferType* scaledFb;

} MyInstance, *MyInstancePtr;

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

static void displace(const uint_32* mask, const uint_32* in,
                     uint_32* out, int xsize, int ysize,
                     double amount, double angle);

static void displace_exact(const uint_32* mask, const uint_32* in,
                           uint_32* out, int xsize, int ysize,
                           double amount, double angle);

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

  if (my == 0)
  {
    s_log(0, "Could not allocate memory for MyInstance struct\n");
    return 0;
  }

  my->scaledFb = 0;

  return my;
}

void destruct(MyInstance* my)
{
  if (my->scaledFb != 0)
    framebuffer_deleteInstance(my->scaledFb);

  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  double amount = trim_double(inst->in_amount->number, 0, 1);
  double angle  = trim_double(inst->in_angle->number, 0, 360);

  uint_32* fb1 = 0;
  uint_32* fb2 = 0;
  int didScale = 0;

  int xsize = 0, ysize = 0;

  scale_framebuffers(inst->in_displ_mask, inst->in_in,
                     &my->scaledFb, &fb1, &fb2,
                     &xsize, &ysize, &didScale);

  // scale output framebuffer to the size of the inputs
  {
    FrameBufferAttributes attribs;
		
    attribs.xsize = xsize;
    attribs.ysize = ysize;
    framebuffer_changeAttributes(inst->out_out, &attribs);
  }

  if (strcmp(inst->in_mode->text, "exact") == 0)
    displace_exact(fb1, fb2, inst->out_out->framebuffer,
             xsize, ysize, amount, angle);
  else
    displace(fb1, fb2, inst->out_out->framebuffer,
             xsize, ysize, amount, angle);

  // delete scaled framebuffer if we didn't need it this time
  if (didScale == 0 && my->scaledFb != 0)
    {		
      framebuffer_deleteInstance(my->scaledFb);
      my->scaledFb = 0;	
    }
}


static void displace(const uint_32* mask, const uint_32* in,
                     uint_32* out, int xsize, int ysize,
                     double amount, double angle)
{
  int x, y, index = 0;

  double s = sin(angle * M_PI / 180.);
  double c = cos(angle * M_PI / 180.);

  int fx = (int) (c * amount * 255 + .5);
  int fy = (int) (s * amount * 255 + .5);

  /*int dx_max = ((255*3 - 382) >> 2) * fx;
  int dy_max = ((255*3 - 382) >> 2) * fy;
  int dx_min = ((-382) >> 2) * fx;
  int dy_min = ((-382) >> 2) * fy;*/

  //  for (y = 0; y < dy_min; ++y)
    //  for (y = dy_min; y < dy_max; ++y)
  for (y = 0; y < ysize; ++y)
    for (x = 0; x < xsize; ++x)
      {
        uint_8* rgb_mask = (uint_8*) (mask + index);

        int b = rgb_mask[0];
        int g = rgb_mask[1];
        int r = rgb_mask[2];
        int grey = (b + g + r) >> 2;

        int dx = (fx * grey) >> 8;
        int dy = (fy * grey) >> 8;

        int x_new = min(max(x + dx, 0), xsize-1);
        int y_new = min(max(y + dy, 0), ysize-1);
        
        out[index] = in[x_new + xsize*y_new];

        ++index;
      }
}


#define PIX_SCALE(dst, sc, pix)  { \
   uint_8* p = (uint_8*) &(pix);   \
   (dst)[0] = (sc) * p[0];         \
   (dst)[1] = (sc) * p[1];         \
   (dst)[2] = (sc) * p[2]; } 

#define PIX_ADD4_SR(dst, p1, p2, p3, p4, s) { \
   (dst)[0] = ((p1)[0] + (p2)[0] + (p3)[0] + (p4)[0]) >> (s); \
   (dst)[1] = ((p1)[1] + (p2)[1] + (p3)[1] + (p4)[1]) >> (s); \
   (dst)[2] = ((p1)[2] + (p2)[2] + (p3)[2] + (p4)[2]) >> (s); }

#define PIX_ROUND(dst, p)  {     \
   (dst)[0] = (p)[0] >> 8;       \
   (dst)[1] = (p)[1] >> 8;       \
   (dst)[2] = (p)[2] >> 8; } 

static void displace_exact(const uint_32* mask, const uint_32* in,
                           uint_32* out, int xsize, int ysize,
                           double amount, double angle)
{
  int x, y, index = xsize + 1;

  double s = sin(angle * M_PI / 180.);
  double c = cos(angle * M_PI / 180.);

  int fx = (int) (c * amount * 255 + .5);
  int fy = (int) (s * amount * 255 + .5);

  for (y = 1; y < ysize-1; ++y)
    {
      for (x = 1; x < xsize-1; ++x)
        {
          uint_8* rgb_mask = (uint_8*) (mask + index);

          int b = rgb_mask[0];
          int g = rgb_mask[1];
          int r = rgb_mask[2];
          int grey = (b + g + r) >> 2;

          int dx = fx * grey;
          int dy = fy * grey;

          int subpixel_x = dx & 0xff;
          int subpixel_y = dy & 0xff;

          int pixel_x = dx >> 8;
          int pixel_y = dy >> 8;

          int x_new = min(max(x + pixel_x, 0), xsize-1);
          int y_new = min(max(y + pixel_y, 0), ysize-1);        

          int pos1 = x_new + xsize * y_new;

          uint_32 p1 = *(in + pos1);
          uint_32 p2 = *(in + pos1 + 1);
          uint_32 p3 = *(in + pos1 + 1 - xsize);
          uint_32 p4 = *(in + pos1 - xsize);

          uint_32 ext1[4], ext2[4], ext3[4], ext4[4];
          uint_32 avg[4];
          uint_8 val[4];

          PIX_SCALE(ext1, 510-subpixel_x-subpixel_y, p1);
          PIX_SCALE(ext2, subpixel_x + 255 - subpixel_y, p2);
          PIX_SCALE(ext3, subpixel_x + subpixel_y, p3);
          PIX_SCALE(ext4, subpixel_y + 255 - subpixel_x, p4);
          
          PIX_ADD4_SR(avg, ext1, ext2, ext3, ext4, 2);

          PIX_ROUND(val, avg);
          out[index] = *((uint_32*) val);

          ++index;
        }

      index += 2;
    }
}
