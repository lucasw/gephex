/* Quartz Output driver.
  Copyright (C) 2007 Georg Seidel
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/

/**
 * TODO
 *
 * - better event handling (it might be possible to quit the event loop
 *    once and for all as mplayer does it)
 * - on PPC, red and blue are flipped
 * - blit parameters (brightness/contrast/gamma, morroring)
 * - support for multiple monitors
 * - resize, set_top and frame
 * - support for fullscreen?
 * - nicer icon
 * - test on intel macs and on 10.4
 * - improve speed of blit operation
 */

#include "quartzoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <Carbon/Carbon.h>

#include "libscale.h"
#include "outputdriver.h"

//-----------------------------------------------------------------------

int Quartz_init(char* error_text, int text_len)
{
  OSStatus status;
  ProcessSerialNumber myProc;

  status = GetCurrentProcess(&myProc);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "GetCurrentProcess() failed with code %d",
	       status);
      return 0;
    }

  status = TransformProcessType(&myProc,
				kProcessTransformToForegroundApplication);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "TransformProcessType() failed with code %d",
	       status);
      return 0;
    }

  status = SetFrontProcess(&myProc);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "SetFrontProcess() failed with code %d",
	       status);
      return 0;
    }

  return 1;
}

//-----------------------------------------------------------------------

struct DriverInstance
{
  WindowRef wnd;
  WindowGroupRef group;

  unsigned int win_xsize;
  unsigned int win_ysize;
};

//-----------------------------------------------------------------------

static struct DriverInstance* Quartz_new_instance(const char* server_name,
                                                  int xpos, int ypos,
                                                  int width, int height,
                                                  int mmx_supported,
                                                  char* error_text, int buflen);

static void Quartz_destroy(struct DriverInstance* sh);

static int Quartz_resize(struct DriverInstance* sh,int width, int height,
                      char* error_text, int text_len);

static int Quartz_blit(struct DriverInstance* sh,
                    const unsigned char* fb, int width, int height,
                    struct blit_params* params,
                    char* error_text, int buflen);

static int Quartz_window_pos(struct DriverInstance* self, int* xpos, int* ypos,
                          char* error_text, int text_len);

static int Quartz_frame(struct DriverInstance* self, int frame_visible,
                     char* error_text, int text_len);

static int Quartz_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len);

static int Quartz_to_monitor(struct DriverInstance* self, int monitor,
                          char* error_text, int text_len);

//-----------------------------------------------------------------------

static int create_window(WindowRef* wnd,
			 WindowGroupRef* group,
			 int xpos, int ypos,
			 int width, int height,
                         char* error_text, int text_len);

static void kill_window(WindowRef wnd, WindowGroupRef group);

static int set_top(WindowRef wnd, int top_most, char* error_text, int text_len);

static void get_error_text(char* buffer, int len);

static int window_get_rect(WindowRef hwnd, int* xpos, int* ypos, 
                           int* xsize, int* ysize,
			   char* error_text, int text_len);

static int window_resize(WindowRef hwnd, int xsize, int ysize,
			 char* error_text, int text_len);

//-----------------------------------------------------------------------

struct OutputDriver* Quartz_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->new_instance  = Quartz_new_instance;
  drv->destroy       = Quartz_destroy;
  drv->resize        = Quartz_resize;
  drv->blit          = Quartz_blit;
  drv->window_pos    = 0; //Quartz_window_pos;
  drv->frame         = 0; //Quartz_frame;
  drv->always_on_top = 0; //Quartz_always_on_top;
  drv->to_monitor    = 0; //Quartz_to_monitor;

  drv->inst          = 0;
  return drv;
}

//-----------------------------------------------------------------------


static struct DriverInstance*
Quartz_new_instance(const char* server_name,
		    int xpos, int ypos,
		    int width, int height, int mmx_support,
		    char* error_text, int buflen)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));

  if (sh == 0)
    {
      snprintf(error_text, buflen,
	       "Quartz_new_instance: Could not allocate memory");
      return 0;
    }

  sh->win_xsize = width;
  sh->win_ysize = height;

  if  (create_window(&sh->wnd, &sh->group,
		     xpos, ypos,
		     width, height,
		     error_text, buflen) != 1)
    {
      free(sh);
      return 0;
    }

  return sh;
}

static void Quartz_destroy(struct DriverInstance* sh)
{
  kill_window(sh->wnd, sh->group);
  free(sh);
}

static int Quartz_resize(struct DriverInstance* sh, int width, int height,
			 char* error_text, int text_len)
{ 
  if (sh->win_xsize != width || sh->win_ysize != height)
    {
      sh->win_xsize = width;
      sh->win_ysize = height;

      return window_resize(sh->wnd, width, height, error_text, text_len);
    }
    return 1;
}

static int Quartz_blit(struct DriverInstance* sh,
		       const unsigned char* fb,
		       int width, int height,
		       struct blit_params* params,
		       char* error_text, int text_len)
{
  CGDataProviderRef dp = CGDataProviderCreateWithData(0,
						      fb,
						      width*height*4,
						      0);

  CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
  CGImageRef img = CGImageCreate(width,
				 height,
				 8,
				 32,
				 width*4,
				 colorSpace,
				 kCGImageAlphaNoneSkipLast, // TODO
				 dp,
				 0,
				 0, //1,
				 kCGRenderingIntentDefault);

  CGContextRef context;
  OSStatus status = QDBeginCGContext(GetWindowPort(sh->wnd), &context);
  if (status != noErr)
    {
      CGImageRelease(img);
      CGDataProviderRelease(dp);
      CGColorSpaceRelease(colorSpace);
      snprintf(error_text, text_len,
	       "QDBeginCGContext() failed with code %d",
	       status);
      return 0;
      }

  CGRect bounds = CGRectMake(0, 0, sh->win_xsize, sh->win_ysize);

  CGContextDrawImage(context, bounds, img);

  // Without this call, the window is not redrawn.
  CGContextSynchronize(context);

  status = QDEndCGContext(GetWindowPort(sh->wnd), &context);
  if (status != noErr)
    {
      CGImageRelease(img);
      CGDataProviderRelease(dp);
      CGColorSpaceRelease(colorSpace);
      snprintf(error_text, text_len,
	       "QDEndCGContext() failed with code %d",
	       status);
      return 0;
    }

  CGImageRelease(img);
  CGDataProviderRelease(dp);
  CGColorSpaceRelease(colorSpace);

  // TODO: hack, care for events since no event loop is running
  EventRef theEvent;
  if  (ReceiveNextEvent(0, NULL,
			0,
			true,
			&theEvent) == noErr)
    {
      SendEventToEventTarget (theEvent, GetEventDispatcherTarget());
      ReleaseEvent(theEvent);
    }

  return 1;
}

static int Quartz_window_pos(struct DriverInstance* self, int* xpos, int* ypos,
                          char* error_text, int text_len)
{
  // TODO
  snprintf(error_text, text_len, "Quartz_window_pos not implemented yet");
  return 0;
  //return window_get_rect(self->wnd, xpos, ypos, 0, 0, error_text, text_len);
}

static int Quartz_frame(struct DriverInstance* self, int frame_visible,
			char* error_text, int text_len)
{
  // TODO
  snprintf(error_text, text_len, "Quartz_frame not implemented yet");
  return 0;
}

static int Quartz_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len)
{
  return set_top(self->wnd, on_top, error_text, text_len);
}

static int Quartz_to_monitor(struct DriverInstance* self, int monitor,
                          char* error_text, int text_len)
{
  snprintf(error_text, text_len, "Quartz_to_monitor not implemented yet");
  return 0;
}

//-----------------------------------------------------------------------

static int create_window(WindowRef* wnd, WindowGroupRef* group,
			 int xpos, int ypos,
			 int width, int height,
                         char* error_text, int text_len)
{
  OSStatus status;

  Rect rect;
  SetRect(&rect, 0, 0, width, height);

  status = CreateNewWindow(kDocumentWindowClass,
			   kWindowStandardHandlerAttribute,
			   &rect,
			   wnd);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "CreateNewWindow() failed with code %d",
	       status);
      return 0;
    }

  status = CreateWindowGroup(0, group);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "CreateWindowGroup() failed with code %d",
	       status);
      DisposeWindow(*wnd);
      return 0;
    }

  status = SetWindowGroup(*wnd, *group);
  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "SetWindowGroup() failed with code %d",
	       status);
      DisposeWindow(*wnd);
      ReleaseWindowGroup(*group);
      return 0;
    }

  CFStringRef title = CFSTR("gephex (quartz video output)");
  status  = SetWindowTitleWithCFString(*wnd, title);
  CFRelease(title);

  if (status != noErr)
    {
      snprintf(error_text, text_len,
	       "SetWindowTitleWithCFString() failed with code %d",
	       status);
      DisposeWindow(*wnd);
      ReleaseWindowGroup(*group);
      return 0;
    }

  RepositionWindow(*wnd, 0, kWindowCenterOnMainScreen);
  ShowWindow(*wnd);
  
  return 1;
}

static void kill_window(WindowRef wnd, WindowGroupRef group)
{
  DisposeWindow(wnd);
  ReleaseWindowGroup(group);
}

static int window_resize(WindowRef wnd,
			 int xsize, int ysize,
			 char* error_text, int text_len)
{
  snprintf(error_text, text_len, "window_resize not implemented yet");
  return 0;
}

static int set_top(WindowRef wnd, int top_most, char* error_text, int text_len)
{
  snprintf(error_text, text_len, "set_top not implemented yet");
  return 0;
}
