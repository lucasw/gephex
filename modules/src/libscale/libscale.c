#include "libscale.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//---------------------------------------------------------------------------

static int pal_trim(int p)
{
  if (p < 0)
    p = 0;
  if (p > 255)
    p = 255;

  return p;
}

void ls_set_adjustment(ls_adjust_pal pal, double bright,
                       double contrast, double gamma,
                       int invert)
{
  int i;

  for (i = 0; i < 256; ++i)
    {

      int p = i;
      // contrast
      p = pal_trim((int) ((p - 127) * contrast + 127));
      // brightness
      p = pal_trim(p + (int) ((bright-0.5)*255*2) );
      // gamma
      p = pal_trim( (int) (255. * pow(p/255., gamma)) );

      pal[i] = p;
    }

  // invert
  if (invert)
    {
      for (i = 0; i < 256; ++i)
        pal[i] = 255-pal[i];
    }
}

//---------------------------------------------------------------------------

static __inline void apply_pal(uint_32* dstc,
                               const uint_32* col,
                               const ls_adjust_pal pal)
{
  uint_8* src = (uint_8*) col;
  uint_8* dst = (uint_8*) dstc;

  dst[0] = pal[src[0]];
  dst[1] = pal[src[1]];
  dst[2] = pal[src[2]];
}

#define APPLY_PAL(DST, COL, PAL) ({uint_8* src = (uint_8*) &(COL); \
  uint_8* dst = (uint_8*) &(DST); \
  dst[0] = (PAL)[src[0]]; \
  dst[1] = (PAL)[src[1]]; \
  dst[2] = (PAL)[src[2]];} )

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
  int dirx, diry;
  uint_32* current = dst;

  assert (dwidth >= 0 && dheight >= 0);

  if (mirrorx)
    {
      dirx = -1;
      current += dwidth;
    }
  else
    {
      dirx = 1;
    }
      
  if (mirrory)
    {
      diry = -dwidth;
      current += (dheight-1)*dwidth;
    }
  else
    {
      diry = dwidth;
    }

  deltax = (double)swidth  / (double)dwidth;
  deltay = (double)sheight / (double)dheight;

  A = (uint_32) (65536.*deltax);
  B = (uint_32) (65536.*deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;

      for (x = dwidth; x != 0; --x)
        {			
          const uint_32* src_ptr = src_base + (x_a >> 16);
          apply_pal(cx, src_ptr, pal);
          //APPLY_PAL(*cx, src_col, pal);
          x_a += A;
          cx += dirx;
        }
      y_a += B;
      current += diry;
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
  int dirx, diry;
  uint_32* current = dst;

  assert (dwidth >= 0 && dheight >= 0);

  if (dwidth == swidth && dheight == sheight && !mirrorx && !mirrory)
    {
      memcpy(dst, src, dwidth*dheight*sizeof(uint_32));
	  return;
    }

  if (mirrorx)
    {
      dirx     = -1;
      current += dwidth;
    }
  else
    {
      dirx     = 1;
    }
      
  if (mirrory)
    {
      diry = -dwidth;
      current += (dheight-1)*dwidth;
    }
  else
    {
      diry = dwidth;
    }

  deltax = (double)swidth  / (double)dwidth;
  deltay = (double)sheight / (double)dheight;

  A = (uint_32) (65536.*deltax);
  B = (uint_32) (65536.*deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;
      
      for (x = dwidth; x != 0; --x)
        {			
          *cx = src_base[x_a >> 16];
          x_a += A;
          cx += dirx;
        }
      y_a += B;
      current += diry;
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

  A = (uint_32) (65536.*deltax);
  B = (uint_32) (65536.*deltay);

  y_a = 0;

  for (y = dheight; y != 0; --y)
    {
      int x;
      const uint_32* src_base;
      uint_32* cx = current;

      x_a = 0;		
      src_base = src + (y_a >> 16) * swidth;
      
      for (x = dwidth; x != 0; --x)
        {			
          *cx = src_base[x_a >> 16];
          x_a += A;
          ++cx;
        }
      y_a += B;
      current += dwidth;
    }
}

//---------------------------------------------------------------------------
