#ifndef INCLUDED_ADJUST_UTIL_H
#define INCLUDED_ADJUST_UTIL_H

#include "basic_types.h"

typedef uint_8 adjust_pal[256];

void set_adjustment(adjust_pal pal, double bright, double contrast,
                    double gamma, int invert);

void fb_cpy_adjust(uint_32* dst, const uint_32* src,
				   int width, int height, const adjust_pal);

void fb_scale32_adjust(uint_32* dst, int dwidth, int dheight,
                       const uint_32* src, int swidth, int sheight,
                       int mirrorx, int mirrory, const adjust_pal pal);

void fb_scale32(uint_32* dst, int dwidth, int dheight,
                const uint_32* src, int swidth, int sheight,
                int mirrorx, int mirrory);

#endif
