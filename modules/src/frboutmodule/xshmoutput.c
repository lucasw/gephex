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

#include "xshmoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> // for fabs
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>

#include "outputdriver.h"

#include "x11stuff.h"
#include "libscale.h"

//-----------------------------------------------------------------------

#define EPS 0.001

//-----------------------------------------------------------------------

const int MAX_RES = 2048;

struct DriverInstance {
  const char* server_name;

  Display* display;
  Window win;
  GC gc;

  XShmSegmentInfo shminfo;
  XImage* shimage;

  int width;
  int height;

  ls_adjust_pal pal;

  int completion_type;
  int event_pending;

  int depth;
};

static struct DriverInstance*
XShm_new_instance(const char* server_name,
                  int xpos, int ypos,
                  int width, int height,
                  char* error_text, int text_len);

static void XShm_destroy(struct DriverInstance* sh);

static int  XShm_resize(struct DriverInstance* sh,int width, int height,
                        char* error_text, int text_len);

static int  XShm_blit(struct DriverInstance* sh,
                      const unsigned char* fb,
                      int width, int height,
                      struct blit_params* params,
                      char* error_text, int text_len);

static int XShm_window_pos(struct DriverInstance* self, int* xpos,
                           int* ypos, char* error_text, int text_len);

static int XShm_frame(struct DriverInstance* self, int frame_visible,
                     char* error_text, int text_len);

static int XShm_always_on_top(struct DriverInstance* self, int on_top,
                             char* error_text, int text_len);

struct OutputDriver* XShm_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));
  drv->new_instance  = XShm_new_instance;
  drv->destroy       = XShm_destroy;
  drv->resize        = XShm_resize;
  drv->blit          = XShm_blit;
  drv->window_pos    = XShm_window_pos;
  drv->frame         = XShm_frame;
  drv->always_on_top = XShm_always_on_top;
  drv->to_monitor    = 0;

  drv->inst          = 0;
  return drv;
}

/***************************************************************************/

/* find the best visual  
 */  
static int find_best_visual_bpp(Display* dpy,
                                XVisualInfo* chosen_vis,
                                int bpp)
{  
  int n = 0;
  int mask = VisualScreenMask | VisualDepthMask | VisualClassMask;
  //    | VisualRedMaskMask | VisualGreenMaskMask | VisualBlueMaskMask;
  //    | VisualBitsPerRGBMask;

  XVisualInfo   vinfo_templ;
  XVisualInfo*  vinfos;

  vinfo_templ.screen     = DefaultScreen(dpy);
  vinfo_templ.depth      = bpp;
  vinfo_templ.class      = TrueColor;
  //  vinfo_templ.red_mask   = 0x000000ff;
  //  vinfo_templ.green_mask = 0x0000ff00;
  //  vinfo_templ.blue_mask  = 0x00ff0000;
  //  vinfo_templ.bits_per_rgb  = 8;
  
  vinfos = XGetVisualInfo(dpy, mask, &vinfo_templ, &n);
  /*for (i = 0; i < n; ++i)
    {
      print_visual(vinfos + i);
    }
    printf("-----------------------------------------------------\n");*/
  //  getchar();

  if (vinfos == 0)
    {
      return 1;
    }
  else
    {      
      *chosen_vis = *vinfos;
      XFree(vinfos);
      return 0;
    }
}

static int find_best_visual(Display* dpy,
                            XVisualInfo* chosen_vis)
{ 
  if (find_best_visual_bpp(dpy, chosen_vis, 24) == 0)
    return 0;
  else
    return find_best_visual_bpp(dpy, chosen_vis, 16);
}

static void convert_to_16_inplace(unsigned char* frb,
                                  int width, int height)
{
  const unsigned char* src = frb;
  uint_16* dst = (uint_16*) frb;
  int i;

  for (i = width*height; i != 0; --i)
    {
      unsigned char b = src[0] >> 3;
      unsigned char g = src[1] >> 2;
      unsigned char r = src[2] >> 3;
      src += 4;

      *(dst++) = (r << 11) | (g << 5) | b;
    }
}

/***************************************************************************/

static struct DriverInstance*
XShm_new_instance(const char* server_name,
                  int xpos, int ypos,
                  int width, int height,
                  char* error_text, int text_len)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));
  int screen;
  XVisualInfo vis;
  int err;
  const char* server_name_ptr;

  if (width > MAX_RES || height > MAX_RES)
    {
      snprintf(error_text, text_len,
               "Max resolution (%ix%i) exceeded by given resolution (%i,%i)",
               MAX_RES, MAX_RES, width, height);
      return 0;
    }

  if (strcmp(server_name,"default")==0)
    server_name_ptr=getenv("DISPLAY"); // use the DISPLAY environment variable
  else
    server_name_ptr=server_name; // use the userdefined display

  if (server_name_ptr == 0)
    {
      snprintf(error_text, text_len, "Don't know which display to use.\n"
	       "Set the DISPLAY variable!");
      return 0;
    }

  // XShmQueryExtension returns true whenever the xserver supports
  // this extension - but the connect will still fail if we are not on the
  // same machine!
  // Only if server_name_ptr has the form ":<server_nr>"
  // we assume that we are on the same machine.
  if (strlen(server_name_ptr) == 0 || server_name_ptr[0] != ':')
    {
      snprintf(error_text, text_len, "Can't use shm driver on remote"
	       "displays\nUse ximage instead.\n"
	       "(If you want to use your local xserver, set DISPLAY to ':0'"
	       ", not 'localhost:0')");
      return 0;
    }

  printf("xshmoutput: Connecting to '%s'...\n", server_name_ptr);

  sh->display = XOpenDisplay(server_name_ptr);
  if (sh->display == NULL)
    {
      snprintf(error_text, text_len,
               "Cannot connect to X server %s", server_name);
      return 0;
    }

  if (XShmQueryExtension(sh->display) != True)
    {
      snprintf(error_text, text_len,
               "XShm Extension not available for %s", sh->server_name);

      return 0;
    }
  
  sh->completion_type = XShmGetEventBase(sh->display) + ShmCompletion;
  sh->event_pending = 0;

  screen = DefaultScreen(sh->display);
  sh->win = XCreateSimpleWindow(sh->display,
                                RootWindow(sh->display, screen),
                                xpos, ypos,
                                width, height,
                                0, BlackPixel(sh->display, screen),
                                WhitePixel(sh->display, screen));
  //TODO: error handling
  
  XMapWindow(sh->display, sh->win);
  
  sh->gc = XCreateGC(sh->display, sh->win, 0, NULL);

  err = find_best_visual(sh->display, &vis);
  if (err)
    {
      XDestroyWindow(sh->display, sh->win);
      snprintf(error_text, text_len, "Could not find matching visual\n"
               "XServer must be set up at 24 bit depth or 16 bit depth");
      return 0;
    }

  sh->depth = vis.depth;

  /* create shared memory ximage */
  sh->shimage = XShmCreateImage (sh->display,
                                 DefaultVisual(sh->display, screen),
                                 DefaultDepth(sh->display, screen),
                                 ZPixmap,
                                 0, 
                                 &sh->shminfo, width, height);

  if (sh->shimage == 0)
    {
      XDestroyWindow(sh->display, sh->win);
      snprintf(error_text, text_len, "Could not create xshm image");
      return 0;
    }

  /* allocate shared memory */
  sh->shminfo.shmid = shmget (IPC_PRIVATE,
                              MAX_RES * MAX_RES * 4,
                              IPC_CREAT|0777);

  if (sh->shminfo.shmid == -1)
    {
      XDestroyImage(sh->shimage);
      XDestroyWindow(sh->display, sh->win);
      snprintf(error_text, text_len, "shmget() failed!");
      return 0;
    }

  /* attach shared memory to our process */
  sh->shminfo.shmaddr = sh->shimage->data = shmat (sh->shminfo.shmid, 0, 0);

  if (sh->shminfo.shmaddr == -1)
    {
      XDestroyImage(sh->shimage);
      XDestroyWindow(sh->display, sh->win);
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);
      snprintf(error_text, text_len, "shmat() failed!");
    }

  /* the server is not allowed to write to the shared memory */
  sh->shminfo.readOnly = True;

  /* tell the server to attach to the shared memory */
  if (XShmAttach(sh->display, &sh->shminfo) != True)
    {
      shmdt (sh->shminfo.shmaddr);
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);
      XDestroyImage(sh->shimage);
      XDestroyWindow(sh->display, sh->win);

      snprintf(error_text, text_len,
               "Server would not attach to shared memory!");
      return 0;
    }

  sh->width  = width;
  sh->height = height;

  XFlush( sh->display );

  return sh;
}

static void XShm_destroy(struct DriverInstance* sh)
{
  if (sh->shimage != 0)
    XDestroyImage (sh->shimage);

  if (sh->shminfo.shmaddr != 0)
    {
      XShmDetach (sh->display, &sh->shminfo);

      shmdt (sh->shminfo.shmaddr);
      shmctl (sh->shminfo.shmid, IPC_RMID, 0);
    }

  if (sh->gc)
    XFreeGC(sh->display, sh->gc);

  if (sh->win)
    XDestroyWindow(sh->display, sh->win);

  if (sh->display)
    XCloseDisplay(sh->display);

  sh->gc = 0;
  sh->win = 0;
  sh->display = 0;

  free(sh);
}

static int XShm_resize(struct DriverInstance* sh,
                       int width, int height,
                       char* error_text, int text_len)
{ 
  if (sh->width != width || sh->height != height)
    {
      int screen = DefaultScreen(sh->display);

      if (width > MAX_RES || height > MAX_RES)
        {
          snprintf(error_text, text_len,
                   "Max resolution (%ix%i) exceeded by given "
                   "resolution (%i,%i)",
                   MAX_RES, MAX_RES, width, height);
          return 0;
        }

      XResizeWindow(sh->display, sh->win, width, height);

      XDestroyImage(sh->shimage);

      sh->shimage = XShmCreateImage(sh->display,
                                    DefaultVisual(sh->display, screen),
                                    DefaultDepth(sh->display, screen),
                                    ZPixmap,
                                    sh->shminfo.shmaddr, 
                                    &sh->shminfo, width, height);

      sh->width  = width;
      sh->height = height;
    }
  return 1;
}

static int XShm_blit(struct DriverInstance* sh,
                     const unsigned char* fb,
                     int width, int height,
                     struct blit_params* params,
                     char* error_text, int text_len)
{
  int needs_adjust = (fabs(params->brightness-0.5) > EPS 
                      || fabs(params->contrast-1.0) > EPS
                      || fabs(params->gamma-1.0) > EPS
                      || params->invert);

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

  // adjust and scale input framebuffer frb into shared mem
  if (needs_adjust)
    {
      ls_set_adjustment(sh->pal, params->brightness, params->contrast,
                     params->gamma, params->invert);
                     
      ls_scale32m_adjust((uint_32*)sh->shimage->data, sh->width, sh->height,
                        (uint_32*)fb, width, height, params->mirrorx,
                        params->mirrory, sh->pal);
    }
  else
    {
      ls_scale32m((uint_32*)sh->shimage->data, sh->width, sh->height,
                  (uint_32*)fb, width, height, params->mirrorx,
                  params->mirrory);
    }

  if (sh->depth == 16)
    {
      convert_to_16_inplace(sh->shimage->data, sh->width, sh->height);
    }

  // blit shared mem image
  XShmPutImage(sh->display, sh->win, sh->gc, sh->shimage,
               0, 0, 0, 0, sh->width, sh->height, True);
  sh->event_pending = 1;

  XFlush(sh->display);
  //XSync(sh->display, False);
  return 1;
}

static int XShm_window_pos(struct DriverInstance* self, int* xpos,
                           int* ypos, char* error_text, int text_len)
{
  XWindowAttributes attribs;
  XGetWindowAttributes(self->display, self->win, &attribs);
  *xpos = attribs.x;
  *ypos = attribs.y;
  return 1;
}

static int XShm_frame(struct DriverInstance* self,
                      int frame_visible,
                      char* error_text, int text_len)
{
  //  printf("frame = %i\n", frame_visible);
  return x11_win_frame(frame_visible != 0,
                       self->display,
                       self->win);
}

static int XShm_always_on_top(struct DriverInstance* self,
                              int on_top,
                              char* error_text, int text_len)
{
  //  printf("on_top = %i\n", on_top);
  return x11_win_on_top(on_top != 0,
                        self->display,
                        self->win);
}
