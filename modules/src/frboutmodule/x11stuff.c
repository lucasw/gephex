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

#include "x11stuff.h"

int x11_win_on_top(Bool on_top,
                    Display* dpy,
                    Window win)
{
  /*  if (on_top)
    {
      XUnmapWindow( dpy, win );
      XSetTransientForHint(dpy, win,
                           RootWindow(dpy,
                                      DefaultScreen(dpy)));

      XMapRaised( dpy, win );
      XRaiseWindow( dpy, win );
      XFlush(dpy);
      //TODO: error handling
      }*/
  /*  else
    {
    }*/
  return 1;
}


int x11_win_frame(Bool frame,
                   Display* dpy,
                   Window win)
{
  XSetWindowAttributes attr;
  XWindowAttributes attribs;
  int x, y;

  
  XGetWindowAttributes(dpy, win, &attribs);
  x = attribs.x;
  y = attribs.y;

  XUnmapWindow( dpy, win );
  XFlush(dpy);

  attr.override_redirect = ((frame == False) ? True : False);
  //  printf("override_redirect = %i\n", attr.override_redirect);

  XChangeWindowAttributes(dpy, win,
                          CWOverrideRedirect, &attr);

  if (!frame)
    {
      x = y = 0;
    }

  {
    XWindowChanges chg;
    chg.x = x;
    chg.y = y;
    XConfigureWindow(dpy, win, CWX | CWY, &chg);
  }

  XMapWindow( dpy, win );

  XFlush(dpy);
  //TODO: error handling
  return 1;
}

