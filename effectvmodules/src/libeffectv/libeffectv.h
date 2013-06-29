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

/**
 * Note: this library contains code from the EffecTV project!
 * http://effectv.sourceforge.net/
 * Their copyright applies for most parts.
 */

#ifndef INCLUDED_LIBEFFECTTV_H
#define INCLUDED_LIBEFFECTTV_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

/**
 *
 * Simple emulation library, that helps to run EffecTV-effects
 * in GePhex.
 *
 */

/*****************************************************************************/

/**
 * Interface of the emulation library
 */

typedef void (*effectv_lock_funcT)(void);
typedef void (*effectv_unlock_funcT)(void);

struct effectv_Effect;

/**
 * Takes a pointer to a EffecTV register function
 */
struct effectv_Effect* effectv_init(void* register_func,
                                    effectv_lock_funcT lock_func,
                                    effectv_unlock_funcT unlock_func);

int effectv_draw(struct effectv_Effect* effect,
                  unsigned char* vid, unsigned char* screen,
		  int xsize, int ysize);


void effectv_teardown(struct effectv_Effect* effect);

/*****************************************************************************/

/**
 * Necessary global vars and functions for the EffecTV effects
 */
extern int video_width;
extern int video_height;
extern int video_area;
extern int screen_width;
extern int screen_height;
extern int screen_scale;
extern int stretch;


#if defined(OS_WIN32)
void bzero(void* ptr, int size);
#endif
/*****************************************************************************/

#endif

