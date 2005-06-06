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

#ifndef INCLUDED_X11_STUFF_H
#define INCLUDED_X11_STUFF_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <X11/extensions/XShm.h>
#include <X11/extensions/Xvlib.h>

#include "basic_types.h"

/**
 * X11 helper functions.
 */

/**
 * Moves a window to top / from top.
 * \param on_top if True, the window is moved on top
 *               if False, the window is no longer on top
 * \param dpy the display of the window
 * \param win the window
 * \return 0 on error
 */
int x11_win_on_top(Bool on_top,
                   Display* dpy,
                   Window win);

/**
 * Removes/adds a frame (+ window decoration).
 * \param on_top if True, the decoration is removed
 *               if False, the window decoration is restored
 * \param dpy the display of the window
 * \param win the window
 * \return 0 on error
 */
int x11_win_frame(Bool frame, Display* dpy, Window win);

/* find the best visual  
 */  
int find_best_visual(Display* dpy,
                     XVisualInfo* chosen_vis);


void convert_to_16_inplace(uint8_t* frb, int width, int height);

int big_endian();
void convert_endianness(uint8_t* frb, int width, int height);

//void print_visual(XVisualInfo* vinfo);

int check_xshm_extension(Display* dpy);

int check_xv_extension(Display* dpy);


#endif
