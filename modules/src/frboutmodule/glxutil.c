/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2003 

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

#include "glutil.h"
#include <string.h>
#include <GL/glx.h>		/* this includes the necessary X headers */

//static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
//static int dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
static Display *s_dpy;
static Window s_win;
static GLXContext s_cx;
static int s_xsize;
static int s_ysize;

/*static void print_visual(XVisualInfo* vinfo)
{
  printf("Visual %i: {\n", vinfo->visualid);
  printf("\tDepth\t\t: %i\n", vinfo->depth);
  printf("\tclass\t\t: %i\n", vinfo->class);
  printf("\tred_mask\t\t: %.8x\n", vinfo->red_mask);
  printf("\tgreen_mask\t\t: %.8x\n", vinfo->green_mask);
  printf("\tblue_mask\t\t: %.8x\n", vinfo->blue_mask);
  printf("\tcolormap_size\t\t: %.8x\n", vinfo->colormap_size);
  printf("\tbits_per_rgb\t\t: %i\n", vinfo->bits_per_rgb);
  printf("}\n");
}*/

// init a opengl window by the native windowsystem
int initOutput(const char* caption, const char* display_name,
	       int xres, int yres, int bpp)
{
  int dummy; // only to trick the glxquery fun
  XVisualInfo  *vi; // to store some info abot the screen
  Colormap cmap;
  int AttributeList[] = {GLX_RGBA, GLX_DOUBLEBUFFER, None};
  XSetWindowAttributes swa;

  s_xsize = xres;
  s_ysize = yres;

  // open a new connection to the X server
  const char* display_name_ptr;
  if (strcmp(display_name,"default")==0)
    display_name_ptr=0; // use the DISPLAY environment variable
  else
    display_name_ptr=display_name; // use the userdefined display
  
  s_dpy = XOpenDisplay(display_name_ptr);
  
  
  if (s_dpy == NULL)
    return 0;

  // make sure OpenGL's GLX extension supported
  if(!glXQueryExtension(s_dpy, &dummy, &dummy)) return 0;

  /* Get an appropriate visual */
  vi = glXChooseVisual(s_dpy, DefaultScreen(s_dpy), AttributeList);

  //print_visual(vi);


  /* Create a GLX context */
  s_cx = glXCreateContext(s_dpy, vi, 0, GL_TRUE);

  /* Create a colormap */
  cmap = XCreateColormap(s_dpy, RootWindow(s_dpy, vi->screen),
			 vi->visual, AllocNone);

  /* Create a window */
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.event_mask = StructureNotifyMask;

  s_win = XCreateWindow(s_dpy, RootWindow(s_dpy, vi->screen), 0,
			  0, s_xsize, s_ysize, 0, vi->depth,
			  InputOutput, vi->visual,
			  CWBorderPixel|CWColormap|CWEventMask, &swa);

  XSetStandardProperties(s_dpy, s_win, caption, caption, None, NULL, 0, NULL);

  /* Connect the context to the window */
  glXMakeCurrent(s_dpy, s_win, s_cx);

  XMapWindow(s_dpy, s_win);

  XFlush(s_dpy);


  glXSwapBuffers(s_dpy, s_win); 
  return 1;
}

void resizeOutput(int new_xsize, int new_ysize)
{
  XResizeWindow(s_dpy, s_win, new_xsize, new_ysize);
  
  XFlush(s_dpy);

  s_xsize = new_xsize;
  s_ysize = new_ysize;

}

void updateOutput(const uint_32* framebuffer)
{
  glXSwapBuffers(s_dpy,s_win);
}

void shutdownOutput()
{
  // remove the current rendering context for gl
  // (otherwise there could be som draw actions left, that
  //  will be flushed when a new gl output is created and cause
  //  the application to crash)
  glXMakeCurrent(s_dpy, None, NULL);

  glXDestroyContext(s_dpy, s_cx);

  XDestroyWindow(s_dpy, s_win);

  // It should be enough to call XCloseDisplay, because it automatically
  // destroys the window
  XCloseDisplay(s_dpy);
}
