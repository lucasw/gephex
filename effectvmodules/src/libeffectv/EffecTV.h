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

/*
 *
 * This is a slightly modified compatibility header, to make EffecTV
 * effects work with GePhex.
 * Taken from EffecTV version 0.3.8
 *
 * Changes made:
 *  -removed includes to other headers
 *  -removed macros and SDL-dependencies
 *  -changes for EffecTV 0.3.9
 */

/*
 * EffecTV - Realtime Digital Video Effector
 * Copyright (C) 2001-2002 FUKUCHI Kentaro
 *
 * EffecTV.h: common header
 *
 */

#ifndef __EFFECTV_H__
#define __EFFECTV_H__

typedef unsigned int RGB32;

#define PIXEL_SIZE (sizeof(RGB32))

typedef struct _effect
{
  char *name;
  int (*start)(void);
  int (*stop)(void);
  int (*draw)(RGB32* src, RGB32* dst);
  int (*event)(void *);
} effect;

typedef effect *effectRegistFunc(void);

extern int debug;

#endif /* __EFFECTV_H__ */
