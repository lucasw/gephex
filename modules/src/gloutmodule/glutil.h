#ifndef _INCLUDED_GL_UTIL_H_
#define _INCLUDED_GL_UTIL_H_

#include "framebuffertype.h"

int initOutput(char* caption, int xsize, int ysize,int bpp);

void resizeOutput(int new_xsize, int new_ysize);

void updateOutput(uint_32* framebuffer);

void shutdownOutput();

#endif
