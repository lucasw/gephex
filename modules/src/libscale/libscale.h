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

#ifndef INCLUDED_LIB_SCALE_H
#define INCLUDED_LIB_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "basic_types.h"

  typedef uint_8 ls_adjust_pal[256];

  /**
   * Inits a colorspace adjustment.
   */
  void ls_set_adjustment(ls_adjust_pal pal,
                         double bright,
                         double contrast,
                         double gamma,
                         int invert);

  /**
   * Copying with colorspace adjustment.
   */
  void ls_cpy_adjust(uint_32* dst, const uint_32* src,
                     int width, int height, const ls_adjust_pal);

  /**
   * Scaling with mirroring and colorspace adjustment.
   */
  void ls_scale32m_adjust(uint_32* dst,       int dwidth, int dheight,
                          const uint_32* src, int swidth, int sheight,
                          int mirrorx, int mirrory, const ls_adjust_pal pal);

  /**
   * Scaling with mirroring
   */
  void ls_scale32m(uint_32* dst,       int dwidth, int dheight,
                   const uint_32* src, int swidth, int sheight,
                   int mirrorx, int mirrory);

  void ls_scale32(uint_32* dst,       int dwidth, int dheight,
                  const uint_32* src, int swidth, int sheight);

#ifdef __cplusplus
}
#endif

#endif
