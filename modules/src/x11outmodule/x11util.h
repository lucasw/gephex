#ifndef INCLUDED_X11_UTIL_H
#define INCLUDED_X11_UTIL_H

#include "basic_types.h"

void fb_scale32(uint_32* dst, int dwidth, int dheight,
                const uint_32* src, int swidth, int sheight);
#endif
