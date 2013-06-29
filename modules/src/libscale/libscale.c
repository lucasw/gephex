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

#include "libscale.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//---------------------------------------------------------------------------

static double pal_trim(double p)
{
  if (p < 0)
    p = 0;
  if (p > 1)
    p = 1;

  return p;
}

void ls_set_adjustment(ls_adjust_pal pal, double bright,
                       double contrast, double gamma,
                       int invert)
{
  int i;

  // invert
  if (invert)
    {
      for (i = 0; i < 256; ++i)
        pal[i] = 255-i;
    }
  else
    {
      for (i = 0; i < 256; ++i)
        pal[i] = i;
    }

  for (i = 0; i < 256; ++i)
    {

      double p = pal[i] / 255.;
      // contrast
      p = pal_trim((p - 0.5)*contrast + 0.5);
      // brightness
      p = pal_trim(p + (bright-0.5)*2);
      // gamma
      p = pal_trim(pow(p, gamma));

      pal[i] = (int) (p*255);
    }
}

//---------------------------------------------------------------------------

static __inline void apply_pal(uint_32* dstc,
                               const uint_32* col,
                               const ls_adjust_pal pal)
{
  const uint_8* src = (const uint_8*) col;
  uint_8* dst = (uint_8*) dstc;

  dst[0] = pal[src[0]];
  dst[1] = pal[src[1]];
  dst[2] = pal[src[2]];
}

//---------------------------------------------------------------------------

void ls_cpy_adjust(uint_32* dst, const uint_32* src, int width, int height,
                   const ls_adjust_pal pal)
{
  uint_32* di = dst;
  const uint_32* si = src;
  uint_32* end = dst+width*height;

  for (; di != end; ++di, ++si)
    {
      apply_pal(di, si, pal);
    }
}

//---------------------------------------------------------------------------

void ls_scale32m_adjust(uint_32* dst, int dwidth, int dheight,
                        const uint_32* src, int swidth, int sheight,
                        int mirrorx, int mirrory, const ls_adjust_pal pal)
{
  int y;
  uint_32 x_a, y_a;
  uint_32 A,B;
  double deltax=.0, deltay=.0;
  const int dirx = mirrorx ? -1 : 1;
  const int diry = mirrory ? -dwidth : dwidth;
  uint_32* current = dst;

  assert (dwidth >= 0 && dheight >= 0);

  if (dwidth == swidth && dheight == sheight && !mirrorx && !mirrory)
    {
      ls_cpy_adjust(dst, src, dwidth, dheight, pal);
      return;
    }

  if (mirrorx)
    current += dwidth-1;
      
  if (mirrory)
    current += (dheight-1)*dwidth;

  deltax = (double)swidth  / (double)dwidth;
  deltay = (double)sheight / (double)dheight;

  A = (uint_32) (65536 * deltax);
  B = (uint_32) (65536 * deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y, y_a += B, current += diry)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;

      for (x = dwidth; x != 0; --x, x_a += A, cx += dirx)
        {			
          const uint_32* src_ptr = src_base + (x_a >> 16);
          apply_pal(cx, src_ptr, pal);
          //APPLY_PAL(*cx, src_col, pal);
        }
    }
}

//---------------------------------------------------------------------------

void ls_scale32m(uint_32* dst, int dwidth, int dheight,
                 const uint_32* src, int swidth, int sheight,
                 int mirrorx, int mirrory)
{
  int y;
  uint_32 x_a, y_a;
  uint_32 A,B;
  double deltax=.0, deltay=.0;
  const int dirx = mirrorx ? -1 : 1;
  const int diry = mirrory ? -dwidth : dwidth;
  uint_32* current = dst;

  assert (dwidth >= 0 && dheight >= 0);

  if (dwidth == swidth && dheight == sheight && !mirrorx && !mirrory)
    {
      memcpy(dst, src, dwidth*dheight*sizeof(uint_32));
      return;
    }

  if (mirrorx)
    current += dwidth-1;
      
  if (mirrory)
    current += (dheight-1)*dwidth;

  deltax = (double)swidth  / (double)dwidth;
  deltay = (double)sheight / (double)dheight;

  A = (uint_32) (65536 * deltax);
  B = (uint_32) (65536 * deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y, y_a += B, current += diry)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;
      
      for (x = dwidth; x != 0; --x, x_a += A, cx += dirx)
        *cx = src_base[x_a >> 16];
    }
}

//---------------------------------------------------------------------------

void ls_scale32(uint_32* dst, int dwidth, int dheight,
                const uint_32* src, int swidth, int sheight)
{
  int y;
  uint_32 x_a, y_a;
  uint_32 A,B;
  double deltax=.0, deltay=.0;
  uint_32* current = dst;

  assert (dwidth >= 0 && dheight >= 0);

  if (dwidth == swidth && dheight == sheight)
    {
      memcpy(dst, src, dwidth*dheight*sizeof(uint_32));
      return;
    }

  deltax = (double)swidth  / (double)dwidth;
  deltay = (double)sheight / (double)dheight;

  A = (uint_32) (65536 * deltax);
  B = (uint_32) (65536 * deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y, y_a += B, current += dwidth)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;
      
      for (x = dwidth; x != 0; --x, x_a += A, ++cx)
        *cx = src_base[x_a >> 16];
    }
}

//---------------------------------------------------------------------------
