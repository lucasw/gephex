#include "glutil.h"

#include <GL/glx.h>		/* this includes the necessary X headers */
#include <GL/gl.h>

//static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
//static int dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
static Display *s_dpy;
static Window s_win;
static GLXContext s_cx;
static int s_xsize;
static int s_ysize;

// init a opengl window by the native windowsystem
int initOutput(char* caption, int xres, int yres, int bpp)
{
  int dummy; // only to trick the glxquery fun
  XVisualInfo  *vi; // to store some info abot the screen
  Colormap cmap;
  int AttributeList[] = {GLX_RGBA, GLX_DOUBLEBUFFER, None};
  XSetWindowAttributes swa;

  s_xsize = xres;
  s_ysize = yres;
  s_dpy = 0;
  
  // open a new connection to the X server
  s_dpy = XOpenDisplay(NULL);
  if (s_dpy == NULL)
    return 0;

  // make sure OpenGL's GLX extension supported
  if(!glXQueryExtension(s_dpy, &dummy, &dummy)) return 0;

  /* Get an appropriate visual */
  vi = glXChooseVisual(s_dpy, DefaultScreen(s_dpy), AttributeList);

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

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glXSwapBuffers(s_dpy, s_win); 

  return 1;
}

void resizeOutput(int new_xsize, int new_ysize)
{
  XResizeWindow(s_dpy, s_win, new_xsize, new_ysize);
  
  XFlush(s_dpy);

  glViewport(0, 0, new_xsize, new_ysize);

  s_xsize = new_xsize;
  s_ysize = new_ysize;
}

void updateOutput(uint_32* framebuffer)
{
  glDrawPixels(s_xsize, s_ysize, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer);

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
  XFlush(s_dpy);
}
