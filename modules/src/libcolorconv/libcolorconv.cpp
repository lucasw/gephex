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

#include "libcolorconv.h"

// debug

#include <iostream>

#include <cassert>
#include <algorithm>

// from fourcc:
//Y  =      0.257*R + 0.504*G + 0.098*B + 16
//Cb = U = -0.148*R - 0.291*G + 0.439*B + 128
//Cr = V =  0.439*R - 0.368*G - 0.071*B + 128
// y range is [16, 235]
// u,v range is [16, 239]
// these are normalized values, before usage substract
// 16 from y and 128 from u, v
static const int32_t yr = (int32_t) (        0.257 * 65536); // 16843
static const int32_t yg = (int32_t) (        0.504 * 65536); // 33030
static const int32_t yb = (int32_t) (        0.098 * 65536); //  6423

static const int32_t ur = (int32_t) (0.25 * -0.148 * 65536); // -2425
static const int32_t ug = (int32_t) (0.25 * -0.291 * 65536); // -4768
static const int32_t ub = (int32_t) (0.25 *  0.439 * 65536); //  7193

static const int32_t vr = (int32_t) (0.25 *  0.439 * 65536); //  7193
static const int32_t vg = (int32_t) (0.25 * -0.368 * 65536); // -6029
static const int32_t vb = (int32_t) (0.25 * -0.071 * 65536); // -1163

namespace
{

  template <typename INT>
  uint8_t uint8_t_sat(INT c)
  {
    //c = std::max(0,std::min(255,c));
    if (c & (~255)) { if (c < 0) c = 0; else c = 255; }
    return c;
  }

  bool is_even(int n) 
  { 
    return n % 2 == 0; 
  }

  struct bgra_t
  {
    uint8_t pixel[4];

    // TODO ifdef für big/little endianess
    // atm only intel x86
    uint8_t& blue()  { return pixel[0]; }
    uint8_t& green() { return pixel[1]; }
    uint8_t& red()   { return pixel[2]; }
    uint8_t& alpha() { return pixel[3]; }
    
    bgra_t(uint8_t red_=0, uint8_t green_=0, uint8_t blue_=0, uint8_t alpha_=0)
    {
      pixel[0]=blue_;
      pixel[1]=green_;
      pixel[2]=red_;
      pixel[4]=alpha_;
    }
    
  };

}
  
void cvt_yuv420p_to_bgra(uint8_t* dst, uint8_t* src,
			 size_t width, size_t height)
{
  // the yuv420p format is only defined for a even width 
  // and a even height
  assert( is_even( width ) );
  assert( is_even( height ) );
  

  // precalced table
  int rv_tab[256];
  int gv_tab[256];
  int gu_tab[256];
  int bu_tab[256];

  for ( int i = 0; i != 256; ++i )
    {
      rv_tab[i]=static_cast<int>( 1.4075 * (i - 128));
      gv_tab[i]=static_cast<int>(-0.7169 * (i - 128));
      gu_tab[i]=static_cast<int>(-0.3455 * (i - 128));
      bu_tab[i]=static_cast<int>( 1.7790 * (i - 128));
    }
  

  const size_t pixels = width * height;

  const uint8_t* y = src;// pixel 0 upper left
  const uint8_t* u = src + pixels; // the u plane follows the y block
  const uint8_t* v = src + 5 * (pixels>>2);  // the v plane follows the u block

  bgra_t* t = reinterpret_cast<bgra_t*>(dst);

  bgra_t* const t_frame_end= t + (width*height);
  while( t != t_frame_end )
    {
 
      bgra_t* const t_line_end= t + width;
      while( t != t_line_end )
	{	
	  int rv = rv_tab[*v];
	  int gv = gv_tab[*v];
	  int gu = gu_tab[*u];
	  int bu = bu_tab[*u];
	  
	  uint8_t y_0 = y[0];
	  t[0] = bgra_t(
			uint8_t_sat( y_0 + rv ),
			uint8_t_sat( y_0 + gv + gu ),
			uint8_t_sat( y_0 + bu ) 
			);

	  uint8_t y_1 = y[1];
	  t[1] = bgra_t(
			uint8_t_sat( y_1 + rv ),
			uint8_t_sat( y_1 + gv + gu ),
			uint8_t_sat( y_1 + bu )
			);

	  uint8_t y_2 = y[width];
	  t[width] = bgra_t(
			    uint8_t_sat( y_2 + rv ),
			    uint8_t_sat( y_2 + gv + gu),
			    uint8_t_sat( y_2 + bu )
			    );

	  uint8_t y_3 = y[width+1];
	  t[width+1] = bgra_t(
			      uint8_t_sat( y_3 + rv ),
			      uint8_t_sat( y_3 + gv + gu ),
			      uint8_t_sat( y_3 + bu )
			      );

	  
	  // increment pointers
	  ++u;
	  ++v;

	  y+=2;
	  t+=2;
	}
      
      // increment pointers
      y+=width;
      t+=width;
      
    }
}



void cvt_rgb32_to_i420(uint8_t* dst, const uint32_t* src,
		       size_t width, size_t height,
		       int* pitches, int* offsets)
{
  const uint32_t* src_ptr = src;
  uint8_t* plane_y = dst + offsets[0];
  uint8_t* plane_u = dst + offsets[1];
  uint8_t* plane_v = dst + offsets[2];
  int x, y;

  int py     = pitches[0];
  int pu     = pitches[1];
  int pv     = pitches[2];
  int h2     = height >> 1;
  int w2     = width >> 1;
  int pad_y  = 2*py - width;
  int pad_u  = pu - w2;
  int pad_v  = pv - w2;

  for (y = h2; y > 0; --y)
    {
      for (x = w2; x > 0; --x)
        {
          const uint8_t* cc1 = (const uint8_t*) (src_ptr);
          const uint8_t* cc2 = (const uint8_t*) (src_ptr+1);
          const uint8_t* cc3 = (const uint8_t*) (src_ptr+width);
          const uint8_t* cc4 = (const uint8_t*) (src_ptr+width+1);

          plane_y[0] = (uint8_t) 
            ( 16 + (((cc1[0] * yb) + (cc1[1] * yg) + (cc1[2] * yr)) >> 16));
          plane_y[1] = (uint8_t) 
            ( 16 + (((cc1[0] * yb) + (cc2[1] * yg) + (cc2[2] * yr)) >> 16));
          plane_y[py] = (uint8_t) 
            ( 16 + (((cc1[0] * yb) + (cc3[1] * yg) + (cc3[2] * yr)) >> 16));
          plane_y[py + 1] = (uint8_t) 
            ( 16 + (((cc1[0] * yb) + (cc4[1] * yg) + (cc4[2] * yr)) >> 16));

          int b = ((int)cc1[0]) +((int)cc2[0]) + ((int)cc3[0]) + ((int)cc4[0]);
          int g = ((int)cc1[1]) +((int)cc2[1]) + ((int)cc3[1]) + ((int)cc4[1]);
          int r = ((int)cc1[2]) +((int)cc2[2]) + ((int)cc3[2]) + ((int)cc4[2]);

          *plane_u = (uint8_t)(128 + ((b*ub + g*ug + r*ur) >> 16));
          *plane_v = (uint8_t)(128 + ((b*vb + g*vg + r*vr) >> 16));

          plane_y += 2;
          src_ptr += 2;
          ++plane_u;
          ++plane_v;
        }

      plane_y += pad_y;
      plane_u += pad_u;
      plane_v += pad_v;
      src_ptr += width;
    }
}


void cvt_rgb16_to_i420(uint8_t* dst, const uint16_t* src,
		       size_t width, size_t height,
		       int* pitches, int* offsets)
{
  // todo
  // printf("Please implement me!\n");
}

