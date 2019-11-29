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

#include "x11output.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> // for fabs
#include <string.h>
#include <assert.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <errno.h>

#include "outputdriver.h"

#include "x11stuff.h"
#include "libscale.h"
#include "libcolorconv.h"


//#define DEBUG_PRINTF printf
#define DEBUG_PRINTF //

//-----------------------------------------------------------------------

#define EPS 0.001

//-----------------------------------------------------------------------

static const int MAX_RES_X = 2560;
static const int MAX_RES_Y = 1600;

static const int USE_XSHM = 0x01;
static const int USE_XV   = 0x02;

//-----------------------------------------------------------------------

/*static int find_best_xv_port(Display* dpy, Window win, XvPortID* xv_port,
                             char* error_text, int text_len);

static int find_best_xv_image_format(Display* dpy, XvPortID port,
                                     int* image_format_id,
                                     char* error_text, int text_len);
*/
static int init_xshm_stuff(struct DriverInstance* sh, char* error_text,
                           int text_len);

static void deinit_xshm_stuff(struct DriverInstance* sh);

static int init_xv_stuff(struct DriverInstance* sh, char* error_text,
                         int text_len);

static void deinit_xv_stuff(struct DriverInstance* sh);

//-----------------------------------------------------------------------

struct DriverInstance {
  int mmx_supported;

  Display* display;
  Window win;
  GC gc;

  XVisualInfo vis;

  int width;
  int height;

  ls_adjust_pal pal;

  int used_extensions; // indicates wether XShm and Xv are used

  uint8_t* data;
  int data_size;

  XImage* ximage;
  int image_width;
  int image_height;

  // used if XShm extension is available
  XShmSegmentInfo shminfo;
  int completion_type;
  int event_pending;

  // used if Xv extension is available
  XvPortID xv_port;
  int xv_format_id;
  XvImage* xv_image;
};


static struct DriverInstance*
X11_new_instance(const char* server_name,
                 int xpos, int ypos,
                 int width, int height, int mmx_supported,
                 char* error_text, int text_len);

static void X11_destroy(struct DriverInstance* sh);

static int  X11_resize(struct DriverInstance* sh,int width, int height,
                        char* error_text, int text_len);

static int  X11_blit(struct DriverInstance* sh,
                      const uint8_t* fb,
                      int width, int height,
                      struct blit_params* params,
                      char* error_text, int text_len);

static int X11_window_pos(struct DriverInstance* self, int* xpos,
                           int* ypos, char* error_text, int text_len);

static int X11_frame(struct DriverInstance* self, int frame_visible,
                     char* error_text, int text_len);

static int X11_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len);

struct OutputDriver* X11_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));
  drv->new_instance  = X11_new_instance;
  drv->destroy       = X11_destroy;
  drv->resize        = X11_resize;
  drv->blit          = X11_blit;
  drv->window_pos    = X11_window_pos;
  drv->frame         = X11_frame;
  drv->always_on_top = X11_always_on_top;
  drv->to_monitor    = 0;

  drv->inst          = 0;
  return drv;
}


static struct DriverInstance*
X11_new_instance(const char* server_name,
                 int xpos, int ypos,
                 int width, int height, int mmx_supported,
                 char* error_text, int text_len)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));
  int screen;
  int err;
  const char* server_name_ptr;

  if (width > MAX_RES_X || height > MAX_RES_Y)
    {
      snprintf(error_text, text_len,
               "Max resolution (%ix%i) exceeded by given resolution (%i,%i)",
               MAX_RES_X, MAX_RES_Y, width, height);
      free(sh);
      return 0;
    }

  sh->mmx_supported   =  mmx_supported;
  sh->width           =  width;
  sh->height          =  height;
  sh->used_extensions =  0;
  sh->data            =  0;
  sh->data_size       =  0;
  sh->ximage          =  0;
  sh->image_width     =  0;
  sh->image_height    =  0;
  sh->shminfo.shmaddr =  0;
  sh->xv_port         =  0xffffffff;
  sh->xv_format_id    = -1;
  sh->xv_image        =  0;
  
  if (strcmp(server_name,"default") == 0)
    server_name_ptr = getenv("DISPLAY"); //use the DISPLAY environment variable
  else
    server_name_ptr = server_name; // use the userdefined display

  if (server_name_ptr == 0)
    {
      snprintf(error_text, text_len,
               "Don't know which display to use. Set the DISPLAY variable!");
      free(sh);
      return 0;
    }

  DEBUG_PRINTF("x11output: Connecting to '%s'...\n", server_name_ptr);

  sh->display = XOpenDisplay(server_name_ptr);
  if (sh->display == NULL)
    {
      snprintf(error_text, text_len,
               "Cannot connect to X server '%s'", server_name);
      free(sh);
      return 0;
    }
  
  if (check_xshm_extension(sh->display))
    {
      if (init_xshm_stuff(sh, error_text, text_len) != 0)
	  sh->used_extensions |= USE_XSHM;
      else
	  printf(" x11output: could not init XShm: '%s', turning off xshm\n",
		 error_text);
    }

  if (check_xv_extension(sh->display))
    {
      sh->used_extensions |= USE_XV;
    }

  screen = DefaultScreen(sh->display);
  sh->win = XCreateSimpleWindow(sh->display,
                                RootWindow(sh->display, screen),
                                xpos, ypos,
                                width, height,
                                0,
                                BlackPixel(sh->display, screen),
                                WhitePixel(sh->display, screen));
  //TODO: error handling
  
  XMapWindow(sh->display, sh->win);
  
  sh->gc = XCreateGC(sh->display, sh->win, 0, NULL);

  err = find_best_visual(sh->display, &sh->vis);
  if (err)
    {
      snprintf(error_text, text_len, "Could not find matching visual\n"
               "XServer must be set up at 24 bit depth or 16 bit depth");
      XDestroyWindow(sh->display, sh->win);
      deinit_xv_stuff(sh);
      free(sh);
      return 0;
    }

  if (sh->vis.depth == 16)
    {
      printf(" x11output: Screen set to 16bit color-depth. You might want to "
	     "switch\n to 24bit for better performance\n");
    }

  if ((sh->used_extensions & USE_XV) == USE_XV)
    {
      if (init_xv_stuff(sh, error_text, text_len) == 0)
        {
          printf(" x11output: turning off Xv support: '%s'\n",
                 error_text);

          sh->used_extensions &= ~USE_XV;
        }
    }

  if ((sh->used_extensions & USE_XSHM) == USE_XSHM)
    {
      if ((sh->used_extensions & USE_XV) == 0)
        {
          /* create shared memory ximage */
          sh->ximage = XShmCreateImage (sh->display,
                                        sh->vis.visual,
                                        sh->vis.depth,
                                        ZPixmap, 0, 
                                        &sh->shminfo, width, height);
          
          if (sh->ximage == 0)
            {
              snprintf(error_text, text_len, "Could not create xshm image");
              deinit_xv_stuff(sh);
              deinit_xshm_stuff(sh);
              XDestroyWindow(sh->display, sh->win);
              free(sh);
              return 0;
            }
          sh->ximage->data = sh->shminfo.shmaddr;
        }
    }

  if (sh->used_extensions & USE_XV)
    printf(" x11output: using Xv extension\n");

  if (sh->used_extensions & USE_XSHM)
    printf(" x11output: using XShm extension\n");

  XFlush( sh->display );

  return sh;
}

static void X11_destroy(struct DriverInstance* sh)
{
  deinit_xv_stuff(sh);

  deinit_xshm_stuff(sh);

  if (sh->ximage != 0)
    {
      sh->ximage->data = 0;
      XDestroyImage(sh->ximage);
      sh->ximage = 0;
    }

  if (sh->gc)
    {
      XFreeGC(sh->display, sh->gc);
      sh->gc = 0;
    }

  if (sh->win)
    {
      XDestroyWindow(sh->display, sh->win);
      sh->win = 0;
    }

  if (sh->display)
    {
      XCloseDisplay(sh->display);
      sh->display = 0;
    }

  if (sh->data)
    {
      free(sh->data);
      sh->data = 0;
    }

  sh->data_size = 0;

  free(sh);
}

static int X11_resize(struct DriverInstance* sh,
		      int width, int height,
		      char* error_text, int text_len)
{ 
  if (sh->width != width || sh->height != height)
    {
      if (width > MAX_RES_X || height > MAX_RES_Y)
        {
          snprintf(error_text, text_len,
                   "Max resolution (%ix%i) exceeded by given "
                   "resolution (%i,%i)",
                   MAX_RES_X, MAX_RES_Y, width, height);
          return 0;
        }

      sh->width  = width;
      sh->height = height;

      XResizeWindow(sh->display, sh->win, width, height);

      if ((sh->used_extensions & USE_XSHM) == USE_XSHM &&
          (sh->used_extensions & USE_XV) == 0)
        {
	  assert(sh->ximage);

	  sh->ximage->data = 0;
          XDestroyImage(sh->ximage);

          sh->ximage = XShmCreateImage(sh->display,
				       sh->vis.visual,
				       sh->vis.depth,
				       ZPixmap,
				       sh->shminfo.shmaddr, 
				       &sh->shminfo, width, height);

	  if (sh->ximage == 0)
	    {
	      snprintf(error_text, text_len, "Could not create XShmImage");
	      return 0;
	    }
        }
    }
  return 1;
}


// xshm and no xv
static int X11_xshm_blit(struct DriverInstance* sh,
                         const uint8_t* fb,
                         int width, int height,
                         struct blit_params* params,
                         int needs_adjust,
                         char* error_text, int text_len)
{
  // wait until last blit has completed
  if (sh->event_pending)
    {
      int max_wait = 15;
      XEvent event;
      sh->event_pending = 0;
      
      while (max_wait--)
        {
          XNextEvent(sh->display, &event);

          if (event.type == sh->completion_type)
            break;
        }
    }

  if (sh->ximage == 0)
    {
      snprintf(error_text, text_len, "Internal error: sh->ximage == 0");
      return 0;
    }
 
  // adjust and scale input framebuffer frb into shared mem
  if (needs_adjust)
    {
      ls_set_adjustment(sh->pal, params->brightness, params->contrast,
			params->gamma, params->invert);
                     
      ls_scale32m_adjust((uint32_t*)sh->ximage->data, sh->width, sh->height,
			 (const uint32_t*)fb, width, height, params->mirrorx,
			 params->mirrory, sh->pal);
    }
  else
    {
      ls_scale32m((uint32_t*)sh->ximage->data, sh->width, sh->height,
                  (const uint32_t*)fb, width, height, params->mirrorx,
                  params->mirrory);
    }

  //TODO: this is a hack for big-endian machines
  if (big_endian())
    convert_endianness(sh->ximage->data, sh->width, sh->height);

  if (sh->vis.depth == 16)
      convert_to_16_inplace(sh->ximage->data, sh->width, sh->height);

  // blit shared mem image
  XShmPutImage(sh->display, sh->win, sh->gc, sh->ximage,
               0, 0, 0, 0, sh->width, sh->height, True);
  sh->event_pending = 1;

  XFlush(sh->display);
  //XSync(sh->display, False);
  return 1;
}

static int X11_xshm_xv_blit(struct DriverInstance* sh,
                            const uint8_t* fb,
                            int width, int height,
                            struct blit_params* params,
                            int needs_adjust,
                            char* error_text, int text_len)
{
  // wait until last blit has completed
  if (sh->event_pending)
    {
      int max_wait = 15;
      XEvent event;
      sh->event_pending = 0;
      
      while (max_wait--)
        {
          XNextEvent(sh->display, &event);

          if (event.type == sh->completion_type)
            break;          
        }
    }


  if (sh->xv_image == 0 ||
      width  != sh->image_width ||
      height != sh->image_height)
    {
      if (sh->xv_image)
        XFree(sh->xv_image);

      sh->xv_image = XvShmCreateImage(sh->display,
                                      sh->xv_port,
                                      sh->xv_format_id,
                                      sh->shminfo.shmaddr,
                                      width, height,
                                      &sh->shminfo);
      sh->image_width  = width;
      sh->image_height = height;
    }

  //TODO: this is a hack for big-endian machines
  if (big_endian())
    convert_endianness((uint8_t*) fb, sh->width, sh->height);

  if (sh->vis.depth == 24)
    {
#if defined(OPT_INCLUDE_MMX)
      if (sh->mmx_supported)
        cvt_rgb32_to_i420_mmx((uint8_t*) sh->xv_image->data,
                              (uint32_t*) fb, width, height,
                              sh->xv_image->pitches, sh->xv_image->offsets);
      else
#endif
        cvt_rgb32_to_i420((uint8_t*) sh->xv_image->data,
                          (uint32_t*) fb, width, height,
                          sh->xv_image->pitches, sh->xv_image->offsets);
    }
  else if (sh->vis.depth == 16)
    cvt_rgb16_to_i420((uint8_t*) sh->xv_image->data,
                      (uint16_t*) fb, width, height,
                      sh->xv_image->pitches, sh->xv_image->offsets);

  // blit shared mem image
  XvShmPutImage(sh->display, sh->xv_port, sh->win, sh->gc, sh->xv_image,
                0, 0, width, height, 0, 0, sh->width, sh->height, True);
  sh->event_pending = 1;

  XFlush(sh->display);
  //XSync(sh->display, False);
  return 1;
}


static int X11_xv_blit(struct DriverInstance* sh,
                       const uint8_t* fb,
                       int width, int height,
                       struct blit_params* params,
                       int needs_adjust,
                       char* error_text, int text_len)
{
  if (sh->xv_image == 0 ||
      width  != sh->image_width ||
      height != sh->image_height)
    {
      if (sh->xv_image)
        XFree(sh->xv_image);

      sh->xv_image = XvCreateImage(sh->display,
                                   sh->xv_port,
                                   sh->xv_format_id,
                                   0,
                                   width, height);
      sh->image_width = width;
      sh->image_height = height;
    }

  if (sh->data == 0 || sh->data_size < sh->xv_image->data_size)
    {
      if (sh->data)
        free(sh->data);

      sh->data = malloc(sh->xv_image->data_size);
      sh->data_size = sh->xv_image->data_size;

      if (sh->data == 0)
	{
	  snprintf(error_text, text_len,
		   "Could not allocate data for XVImage");
	  return 0;
	}
    }

  assert(sh->data);

  //TODO: this is a hack for big-endian machines
  if (big_endian())
   convert_endianness(sh->data, sh->width, sh->height);

  sh->xv_image->data = sh->data;

  if (sh->vis.depth == 24)
    cvt_rgb32_to_i420((uint8_t*) sh->data,
                      (uint32_t*) fb, width, height,
                      sh->xv_image->pitches, sh->xv_image->offsets);
  else if (sh->vis.depth == 16)
    cvt_rgb16_to_i420((uint8_t*) sh->data,
                      (uint16_t*) fb, width, height,
                      sh->xv_image->pitches, sh->xv_image->offsets);

  // blit image
  XvPutImage(sh->display, sh->xv_port, sh->win, sh->gc, sh->xv_image,
             0, 0, width, height, 0, 0, sh->width, sh->height);

  XFlush(sh->display);
  //XSync(sh->display, False);
  return 1;
}


static int X11_ximage_blit(struct DriverInstance* sh,
                           const uint8_t* fb,
                           int width, int height,
                           struct blit_params* params,
                           int needs_adjust,
                           char* error_text, int text_len)
{
  uint8_t* framebuffer = 0;

  if (width != sh->width || height != sh->height ||
      params->mirrorx || params->mirrory || needs_adjust)
    {
      int size = sh->width*sh->height*4;

      if (sh->data && sh->data_size < size)
	{
	  free(sh->data);
	  sh->data = 0;
	}

      if (sh->data == 0)
        {
          sh->data = malloc(size);
          sh->data_size = size;
        }

      if (sh->data == 0)
	{
	  snprintf(error_text, text_len,
		   "Could not allocate data for XImage");
	  return 0;
	}

      if (needs_adjust)
        {            
          ls_scale32m_adjust((uint32_t*) sh->data, sh->width, sh->height,
                             (const uint32_t*) fb, width, height,
			     params->mirrorx, params->mirrory, sh->pal);
        }
      else
        {
          ls_scale32m((uint32_t*) sh->data, sh->width, sh->height,
                      (const uint32_t*) fb, width, height,
		      params->mirrorx, params->mirrory);
        }

      framebuffer = sh->data;
    }
  else
    {
      if (sh->data != 0)
        {
          free(sh->data);
          sh->data = 0;
          sh->data_size = 0;
        }

      assert(width == sh->width);
      assert(height == sh->height);

      framebuffer = (uint8_t*) fb;
    }

  assert(framebuffer != 0);

  // now create an XImage using the framebuffers pixel data

  //TODO: this is a hack for big-endian machines
  if (big_endian())
   convert_endianness(framebuffer, sh->width, sh->height);

  if (sh->vis.depth == 16)
    convert_to_16_inplace(framebuffer, sh->width, sh->height);

  if (sh->ximage == 0 ||
      sh->image_width  != sh->width ||
      sh->image_height != sh->height)
    {
      if (sh->ximage)
	{
	  sh->ximage->data = 0;
	  XDestroyImage(sh->ximage);
	}

      sh->ximage = XCreateImage(sh->display,
                                sh->vis.visual,
                                sh->vis.depth,
                                ZPixmap,
                                0,
                                0,
                                sh->width,
                                sh->height,
                                32,
                                0);

      sh->image_width  = sh->width;
      sh->image_height = sh->height;
    }

  if (sh->ximage == 0)
    {
      snprintf(error_text, text_len, "Could not create XImage!");
      return 0;
    }

  sh->ximage->data = framebuffer;

  // ... blit it to screen
  XPutImage(sh->display, sh->win, sh->gc, sh->ximage, 0, 0, 0, 0,
            sh->width, sh->height);

  // and finally make sure the xserver performs the blitting
  XFlush(sh->display);
  //XSync(sh->display, 0);
  return 1;
}

static int X11_blit(struct DriverInstance* sh,
                     const uint8_t* fb,
                     int width, int height,
                     struct blit_params* params,
                     char* error_text, int text_len)
{
  int needs_adjust = (fabs(params->brightness-0.5) > EPS 
                      || fabs(params->contrast-1.0) > EPS
                      || fabs(params->gamma-1.0) > EPS
                      || params->invert);

  if (needs_adjust)
    ls_set_adjustment(sh->pal, params->brightness, params->contrast,
                      params->gamma, params->invert);

  if ((sh->used_extensions & USE_XSHM) == USE_XSHM)
    {
      if ((sh->used_extensions & USE_XV) == USE_XV)
        return X11_xshm_xv_blit(sh, fb, width, height, params,
                                needs_adjust, error_text, text_len);
      else
        return X11_xshm_blit(sh, fb, width, height, params,
                             needs_adjust, error_text, text_len);
    }
  else
    {
      if ((sh->used_extensions & USE_XV) == USE_XV)
        return X11_xv_blit(sh, fb, width, height, params,
                           needs_adjust, error_text, text_len);
      else
        return X11_ximage_blit(sh, fb, width, height, params,
                               needs_adjust, error_text, text_len);
    }
}

static int X11_window_pos(struct DriverInstance* self, int* xpos,
                           int* ypos, char* error_text, int text_len)
{
  XWindowAttributes attribs;
  XGetWindowAttributes(self->display, self->win, &attribs);
  *xpos = attribs.x;
  *ypos = attribs.y;
  return 1;
}

static int X11_frame(struct DriverInstance* self,
                      int frame_visible,
                      char* error_text, int text_len)
{
  return x11_win_frame(frame_visible != 0,
                       self->display,
                       self->win);
}

static int X11_always_on_top(struct DriverInstance* self,
                              int on_top,
                              char* error_text, int text_len)
{
  return x11_win_on_top(on_top != 0,
                        self->display,
                        self->win);
}

/***************************************************************************/

static int find_best_xv_port(Display* dpy, Window win, XvPortID* xv_port,
                             char* error_text, int text_len)
{
  unsigned int num_adaptors;
  XvAdaptorInfo* adaptors;
  int ret;
  unsigned int i;

  DEBUG_PRINTF("Looking for port...\n");

  ret = XvQueryAdaptors(dpy, win, &num_adaptors, &adaptors);

  switch (ret)
    {
    case Success:
      break;
    case XvBadExtension: 
      snprintf(error_text, text_len,
               "Xv Extension not available for this display");
      return 0;
    case XvBadAlloc:
      snprintf(error_text, text_len,
               "XvQueryAdaptors could not allocate memory");
      return 0;
    default:
      snprintf(error_text, text_len,
               "XvQueryAdaptors: unknown error");
      return 0;
    }

  if (num_adaptors == 0)
    {
      snprintf(error_text, text_len, "No adaptors found");
      XvFreeAdaptorInfo(adaptors);
      return 0;
    }

  // grab first free port (TODO)
  for (i = 0; i < num_adaptors; ++i)
    {
      XvAdaptorInfo* ai = adaptors +i;

      DEBUG_PRINTF(" <><> Adaptor #%i (%s):\n", i, ai->name);
      if (ai->type & XvInputMask)
        DEBUG_PRINTF("    - input\n");
      if (ai->type & XvOutputMask)
        DEBUG_PRINTF("    - output\n");
      if (ai->type & XvImageMask)
        DEBUG_PRINTF("    - image\n");
      if (ai->type & XvStillMask)
        DEBUG_PRINTF("    - still\n");
      if (ai->type & XvVideoMask)
        DEBUG_PRINTF("    - video\n");

      if ((ai->type & XvInputMask) && (ai->type & XvImageMask))
        {
          XvPortID base_port = ai->base_id;
          XvPortID port;
          int num_ports = ai->num_ports;

          for (port = base_port; 
               port < base_port + num_ports; ++port)
            {
              int ret = XvGrabPort(dpy, port, CurrentTime);
              if (ret == Success)
                {
                  *xv_port = port;
                  DEBUG_PRINTF("Xv: got port %i\n", (int)port);
                  XvFreeAdaptorInfo(adaptors);
                  return 1;
                } 
              else
                {
                  DEBUG_PRINTF("Xv: could not grab port %i\n", (int)port);
                }
            }
        }
    }
  snprintf(error_text, text_len, "Could not find free port");

  XvFreeAdaptorInfo(adaptors);
  return 0;
}

static int find_best_xv_image_format(Display* dpy, XvPortID port,
                                     int* image_format_id,
                                     char* error_text, int text_len)
{
  XvImageFormatValues* formats;
  int num_formats;
  int i;

  const int FORMAT_I420 = 0x30323449;

  DEBUG_PRINTF("looking for image formats...\n");

  formats = XvListImageFormats(dpy, port, &num_formats);

  if (formats == 0 || num_formats == 0)
    {
      snprintf(error_text, text_len,
               "XvListImageFormats returned 0 formats"); 
    }

  for(i = 0; i < num_formats; i++)
    {
      XvImageFormatValues* format = formats + i;
      
      DEBUG_PRINTF("Xvideo image format: 0x%x (%4.4s) %s\n",
             format->id, (char*)& format->id,
             (format->format == XvPacked) ? "packed" : "planar");
      
      DEBUG_PRINTF("bpp = %i, type = %s\n", format->bits_per_pixel,
             (format->type == XvRGB) ? "rgb" : "yuv");

      if (format->type == XvYUV)
        {
          DEBUG_PRINTF(" sample bits (y,u,v) = (%i, %i, %i)\n",
                 format->y_sample_bits, format->u_sample_bits,
                 format->v_sample_bits);
          DEBUG_PRINTF(" horz period (y,u,v) = (%i, %i, %i)\n",
                 format->horz_y_period, format->horz_u_period,
                 format->horz_v_period);
          DEBUG_PRINTF(" vert period (y,u,v) = (%i, %i, %i)\n",
                 format->vert_y_period, format->vert_u_period,
                 format->vert_v_period);

          DEBUG_PRINTF(" component order %.32s\n", format->component_order);
          DEBUG_PRINTF(" orientation = %s\n",
                 format->scanline_order == XvTopToBottom ? "top to bottom" :
                 "bottom to top");

          if (format->id == FORMAT_I420)
            {
              DEBUG_PRINTF("  found i420\n");
              *image_format_id = format->id;
              return 1;
            }
        }
    }

  snprintf(error_text, text_len, "Could not find good image format");
  return 0;
}

/***************************************************************************/

static int init_xshm_stuff(struct DriverInstance* sh, char* error_text,
                           int text_len)
{
  sh->completion_type = XShmGetEventBase(sh->display) + ShmCompletion;
  sh->event_pending = 0;

  /* allocate shared memory */

  // changed flags from 0777 to 0666, see
  // http://lists.apple.com/archives/unix-porting/2004/Apr/msg00081.html
  sh->shminfo.shmid = shmget (IPC_PRIVATE,
                              MAX_RES_X * MAX_RES_Y * 4,
                              0666 | IPC_CREAT);

  if (sh->shminfo.shmid == -1)
    {
      snprintf(error_text, text_len, "shmget() failed, errno=%i!", errno);
      return 0;
    }

  /* attach shared memory to our process */
  sh->shminfo.shmaddr = shmat (sh->shminfo.shmid, 0, 0);
  if (sh->shminfo.shmaddr == (void*) -1) // TODO
    {
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);
      snprintf(error_text, text_len, "shmat() failed!");
      return 0;
    }

  /* the server is not allowed to write to the shared memory */
  sh->shminfo.readOnly = True;

  /* tell the server to attach to the shared memory */
  if (XShmAttach(sh->display, &sh->shminfo) != True)
    {
      shmdt (sh->shminfo.shmaddr);
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);

      snprintf(error_text, text_len,
               "Server would not attach to shared memory!");
      return 0;
    }

  return 1;
}

static void deinit_xshm_stuff(struct DriverInstance* sh)
{
  if (sh->shminfo.shmaddr != 0)
    {
      XShmDetach (sh->display, &sh->shminfo);

      shmdt (sh->shminfo.shmaddr);
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);

      sh->shminfo.shmaddr = 0;
    }
}

static int init_xv_stuff(struct DriverInstance* sh, char* error_text,
                         int text_len)
{
  int ret = find_best_xv_port(sh->display, sh->win, &sh->xv_port,
                              error_text, text_len);
  if (ret == 0)
    return 0;

  ret = find_best_xv_image_format(sh->display, sh->xv_port,
                                  &sh->xv_format_id,
                                  error_text, text_len);

  if (ret == 0)
    return 0;

  return 1;
}

static void deinit_xv_stuff(struct DriverInstance* sh)
{
  if (sh->xv_port != 0xffffffff)
    {
      XvUngrabPort(sh->display, sh->xv_port, CurrentTime);
      sh->xv_port = 0xffffffff;
    }

  if (sh->xv_image != 0)
    {
      XFree(sh->xv_image);
      sh->xv_image = 0;
    }
}

/***************************************************************************/
