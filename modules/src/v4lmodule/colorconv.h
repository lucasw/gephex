#ifndef INCLUDED_COLORCONV_H
#define INCLUDED_COLORCONV_H

#include <stdint.h>


/**
 * converts an image in yuv411p to an image bgra32
 * xSize and ySize must be multiples of 2
 */
void init_tabs();
void yuv411p_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize);

void rgb32_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize);

#endif
