#include "x11util.h"

#include <assert.h>

void fb_scale32(uint_32* dst, int dwidth, int dheight,
                const uint_32* src, int swidth, int sheight)
{
  if (dwidth == swidth && dheight == sheight)
    {
      memcpy(dst, src, sizeof(*dst)*dwidth*dheight);
    }
  else
    {
  
      int y;
      uint_32 x_a, y_a;
      uint_32 A,B;
      double deltax=.0, deltay=.0;

      assert (dwidth >= 0 && dheight >= 0);

      deltax = (double)swidth  / (double)dwidth;
      deltay = (double)sheight / (double)dheight;

      A = (uint_32) (65536.*deltax);
      B = (uint_32) (65536.*deltay);

      y_a = 0;

      for (y = 0; y < dheight; ++y)
        {
          int x, line_base;
          x_a = 0;		
          line_base = (y_a >> 16) * swidth;
          for (x = 0; x < dwidth; ++x)
            {			
              *dst= src[(x_a >> 16) + line_base];
              ++dst;
              x_a += A;
            }
          y_a += B;
        }
    }
}
