#include "xshmoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for memcpy only

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>

#include "outputdriver.h"

#include "x11util.h"

const int MAX_RES = 1024;

struct DriverInstance {
  const char* server_name;

  Display* display;
  Window win;
  GC gc;

  XShmSegmentInfo shminfo;
  XImage* shimage;

  int width;
  int height;
};

static struct DriverInstance*
XShm_new_instance(const char* server_name,
                  int width, int height,
                  char* error_text, int buflen);

static void XShm_destroy(struct DriverInstance* sh);
static int  XShm_resize(struct DriverInstance* sh,int width, int height);
static int  XShm_blit(struct DriverInstance* sh,
                        const unsigned char* fb, int width, int height,
                      char* error_text, int buflen);


struct OutputDriver* getXShmDriver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));
  drv->new_instance  = XShm_new_instance;
  drv->destroy       = XShm_destroy;
  drv->resize        = XShm_resize;
  drv->blit          = XShm_blit;

  drv->inst          = 0;
  return drv;
}

/***************************************************************************/

static struct DriverInstance*
XShm_new_instance(const char* server_name,
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

  if (XShmQueryExtension(sh->display) != True)
    {
      snprintf(error_text, buflen,
               "XShm Extension not available for %s", sh->server_name);

      return 0;
    }


  screen = DefaultScreen(sh->display);
  sh->win = XCreateSimpleWindow(sh->display,
                                RootWindow(sh->display, screen),
                                0, 0,
                                width, height,
                                0, BlackPixel(sh->display, screen),
                                WhitePixel(sh->display, screen));
  //TODO: error handling
  
  XMapWindow(sh->display, sh->win);
  
  sh->gc = XCreateGC(sh->display, sh->win, 0, NULL);

  /* create shared memory ximage */
  sh->shimage = XShmCreateImage (sh->display,
                                 DefaultVisual(sh->display, screen),
                                 DefaultDepth(sh->display, screen),
                                 ZPixmap,
                                 0, 
                                 &sh->shminfo, width, height);
  /* allocate shared memory */
  sh->shminfo.shmid = shmget (IPC_PRIVATE,
                              MAX_RES * MAX_RES * 4,
                              IPC_CREAT|0777);

  /* attach shared memory to our process */
  sh->shminfo.shmaddr = sh->shimage->data = shmat (sh->shminfo.shmid, 0, 0);

  /* the server is not allowed to write to the shared memory */
  sh->shminfo.readOnly = True;


  /* tell the server to attach to the shared memory */
  if (XShmAttach(sh->display, &sh->shminfo) != True)
    {
      snprintf(error_text, buflen,
               "Server would not attach to shared memory!");
      return 0;
    }

  sh->width  = width;
  sh->height = height;
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

static int XShm_resize(struct DriverInstance* sh, int width, int height)
{ 
  int screen = DefaultScreen(sh->display);
  XResizeWindow(sh->display, sh->win, width, height);

  XDestroyImage(sh->shimage);

  sh->shimage = XShmCreateImage (sh->display,
                                 DefaultVisual(sh->display, screen),
                                 DefaultDepth(sh->display, screen),
                                 ZPixmap,
                                 sh->shminfo.shmaddr, 
                                 &sh->shminfo, width, height);

  sh->width  = width;
  sh->height = height;

  return 0;
}

static int XShm_blit(struct DriverInstance* sh,
                     const unsigned char* fb,
                     int width, int height,
                     char* error_text,
                     int buflen)
{
  fb_scale32(sh->shimage->data, sh->width, sh->height,
             fb, width, height);

  XShmPutImage(sh->display, sh->win, sh->gc, sh->shimage,
               0, 0, 0, 0, sh->width, sh->height, False);

  XFlush(sh->display);
  return 0;
}
