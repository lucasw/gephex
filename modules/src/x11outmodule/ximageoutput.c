#include "ximageoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "outputdriver.h"

#include "x11util.h"

struct DriverInstance {
  Display* display;
  Window win;
  GC gc;

  int width;
  int height;

  unsigned char* data;
  int data_size;
};

static void print_visual(XVisualInfo* vinfo)
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
}

/* find the best visual  
 */  
static int find_best_visual(Display* dpy,
                            XVisualInfo* chosen_vis)
{  
  int err = 0, n = 0, i;
  int mask = VisualScreenMask | VisualDepthMask | VisualClassMask;
  //    | VisualRedMaskMask | VisualGreenMaskMask | VisualBlueMaskMask;
  //    | VisualBitsPerRGBMask;

  XVisualInfo   vinfo_templ;
  XVisualInfo*  vinfos;

  vinfo_templ.screen     = DefaultScreen(dpy);
  vinfo_templ.depth      = 24;
  vinfo_templ.class      = TrueColor;
  //  vinfo_templ.red_mask   = 0x000000ff;
  //  vinfo_templ.green_mask = 0x0000ff00;
  //  vinfo_templ.blue_mask  = 0x00ff0000;
  //  vinfo_templ.bits_per_rgb  = 8;
  
  vinfos = XGetVisualInfo(dpy, mask, &vinfo_templ, &n);
  /*  for (i = 0; i < n; ++i)
    {
      print_visual(vinfos + i);
    }
  printf("-----------------------------------------------------\n");
  getchar();*/


  if (vinfos == 0)
    return 1;
  else
    {
      *chosen_vis = *vinfos;
      XFree(vinfos);
    }
  
  return err;  
}  



static struct DriverInstance*
XImage_new_instance(const char* server_name,
                    int width, int height,
                    char* error_text, int buflen);

static void XImage_destroy(struct DriverInstance* sh);
static int  XImage_resize(struct DriverInstance* sh,int width, int height);
static int  XImage_blit(struct DriverInstance* sh,
                        const unsigned char* fb, int width, int height,
                        char* error_text, int buflen);


struct OutputDriver* getXImageDriver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  drv->new_instance  = XImage_new_instance;
  drv->destroy       = XImage_destroy;
  drv->resize        = XImage_resize;
  drv->blit          = XImage_blit;

  drv->inst          = 0;
  return drv;
}

/***************************************************************************/

static struct DriverInstance*
XImage_new_instance(const char* server_name,
                    int width, int height,
                    char* error_text, int buflen)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));
  int screen;

  sh->display = XOpenDisplay(server_name);
  if (sh->display == NULL)
    {
      snprintf(error_text, buflen,
               "Cannot connect to X server %s", server_name);
      return 0;
    }

  screen = DefaultScreen(sh->display);
  sh->win = XCreateSimpleWindow(sh->display,
                                RootWindow(sh->display, screen),
                                0, 0,
                                width, height,
                                0,
                                BlackPixel(sh->display, screen),
                                WhitePixel(sh->display, screen));
  //TODO: error handling
  
  XMapWindow(sh->display, sh->win);
  
  sh->gc = XCreateGC(sh->display, sh->win, 0, NULL);

  sh->width     = width;
  sh->height    = height;
  sh->data      = 0;
  sh->data_size = 0;

  return sh;
}

static void XImage_destroy(struct DriverInstance* sh)
{
  if (sh->gc)
    XFreeGC(sh->display, sh->gc);

  if (sh->win)
    XDestroyWindow(sh->display, sh->win);

  if (sh->display)
    XCloseDisplay(sh->display);

  sh->gc = 0;
  sh->win = 0;
  sh->display = 0;

  if (sh->data)
    free(sh->data);

  sh->data = 0;
  sh->data_size = 0;

  free(sh);
}

static int XImage_resize(struct DriverInstance* sh, int width, int height)
{ 
  XResizeWindow(sh->display, sh->win, width, height);

  sh->width  = width;
  sh->height = height;

  return 0;
}

static int XImage_blit(struct DriverInstance* sh,
                       const unsigned char* fb,
                       int width, int height,
                       char* error_text, int buflen)
{
  XVisualInfo vis;
  unsigned char* framebuffer;
  XImage* img;
  int err;

  if (width != sh->width || height != sh->height)
    {
      int size = sh->width*sh->height*4;

      if (sh->data == 0)
        {
          sh->data = malloc(size);
          sh->data_size = size;
        }
      else if (sh->data_size < size)
        {
          free(sh->data);
          sh->data = malloc(size);
          sh->data_size = size;
        }
      
      fb_scale32(sh->data, sh->width, sh->height,
                 fb, width, height);

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

      framebuffer = (unsigned char*) fb;
    }

  err = find_best_visual(sh->display, &vis);
  img = XCreateImage(sh->display,
                     vis.visual,
                     DefaultDepth(sh->display,
                                  DefaultScreen(sh->display)),
                     ZPixmap,
                     0,
                     framebuffer,
                     sh->width,
                     sh->height,
                     32,
                     0);

  if (img == 0)
    {
      snprintf(error_text, buflen, "Could not create XImage!");
      return 1;
    }

  XPutImage(sh->display, sh->win, sh->gc, img, 0, 0, 0, 0,
            sh->width, sh->height);

  XFree(img);

  XFlush(sh->display);
  return 0;
}
