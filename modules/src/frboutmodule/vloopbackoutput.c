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

#include "vloopbackoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include <errno.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>


//TODO: move to common location or similar
#include "../capturemodule/videodev.h"

#include "outputdriver.h"

#include "libscale.h"

#define EPS 0.001

//----------------------------------------------------------------------------

void syserror(const char* blah, char* error_text, int text_len)
{
  /*char buffer[1024];
  int saved_errno = errno;

  buffer[0] = 0;

    if (saved_errno != 0 && strerror_r(errno, buffer, sizeof(buffer)))
    {
      snprintf(error_text, text_len, "%s [errno=%i]\n%s", blah,
               saved_errno, buffer);
    }
    else*/


  const char* err_msg = strerror(errno);
  snprintf(error_text, text_len, "%s\n%s", blah, err_msg);
}

char* strcopy(const char* str)
{
  int l;
  char* r;

  if (str == 0)
    return 0;
  
  l = strlen(str) + 1;
  r = malloc(l);

  memcpy(r, str, l);
  
  return r;
}

//----------------------------------------------------------------------------

int vl_open(const char* dev_name,
            char* error_text, int text_len)
{
  int dev  = open(dev_name, O_RDWR);
  if (dev < 0)
    {
      syserror("Could not open vloopback device",
               error_text, text_len);
      return -1;
    }

  return dev;
}

void vl_close(int dev)
{
  close(dev);
}

// returns 1 on success, 0 on failure
int vl_init(int dev, int width, int height,
            char* error_text, int text_len)
{
  struct video_capability vid_caps;
  struct video_window vid_win;
  struct video_picture vid_pic;

  if (ioctl(dev, VIDIOCGCAP, &vid_caps) == -1)
    {
      syserror("ioctl VIDIOCGCAP", error_text, text_len);
      return 0;
    }

  if (ioctl(dev, VIDIOCGPICT, &vid_pic)== -1)
    {
      syserror("ioctl VIDIOCGPICT", error_text, text_len);
      return 0;
    }

  vid_pic.palette = VIDEO_PALETTE_RGB32;
  if (ioctl(dev, VIDIOCSPICT, &vid_pic) == -1)
    {
      syserror("ioctl VIDIOCSPICT", error_text, text_len);
      return 0;
    }

  if (ioctl(dev, VIDIOCGWIN, &vid_win) == -1)
    {
      syserror("ioctl VIDIOCGWIN", error_text, text_len);
      return 0;
    }

  vid_win.width  = width;
  vid_win.height = height;
  if (ioctl(dev, VIDIOCSWIN, &vid_win) == -1)
    {
      syserror("ioctl VIDIOCSWIN", error_text, text_len);
      return 0;
    }

  return 1;
}

int vl_copy(int dev, const char* framebuffer, int width, int height,
            char* error_text, int text_len)
{
  int size = width*height*4;

  if (write(dev, framebuffer, size) != size)
    {
      syserror("Error writing image!", error_text, text_len);
      return 0;
    }
  return 1;
}

//----------------------------------------------------------------------------

struct DriverInstance {

  char* dev_name;
  int dev;

  int width;
  int height;

  uint_8* data;
  int data_size;

  ls_adjust_pal pal;
};

static struct DriverInstance* 
VLoopback_new_instance(const char* server_name,
                       int xpos, int ypos,
                       int width, int height, int mmx_supported,
                       char* error_text, int text_len);

static void VLoopback_destroy(struct DriverInstance* sh);

static int  VLoopback_resize(struct DriverInstance* sh,
                          int width, int height,
                          char* error_text, int text_len);

static int  VLoopback_blit(struct DriverInstance* sh,
                        const unsigned char* fb,
                        int width, int height,
                        struct blit_params* params,
                        char* error_text, int text_len);

struct OutputDriver* VLoopback_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->new_instance  = VLoopback_new_instance;
  drv->destroy       = VLoopback_destroy;
  drv->resize        = VLoopback_resize;
  drv->blit          = VLoopback_blit;
  drv->window_pos    = 0;
  drv->frame         = 0;
  drv->always_on_top = 0;
  drv->to_monitor    = 0;


  drv->inst          = 0;
  return drv;
}

/***************************************************************************/

static struct DriverInstance*
VLoopback_new_instance(const char* server_name,
                       int xpos, int ypos,
                       int width, int height, int mmx_supported,
                       char* error_text, int text_len)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));

  const char* server_name_ptr;
  if (strcmp(server_name, "default")==0)
    server_name_ptr = "/dev/video0";//TODO: look it up in /proc/video/vloopback
  else
    server_name_ptr = server_name; // use the userdefined output
  
  sh->dev_name  = strcopy(server_name_ptr);
  sh->dev       = vl_open(sh->dev_name, error_text, text_len);

  if (sh->dev == -1 ||
      vl_init(sh->dev, width, height, error_text, text_len) == 0)
    {
      free(sh->dev_name);
      free(sh);
      return 0;
    }

  sh->width     = width;
  sh->height    = height;
  sh->data      = 0;
  sh->data_size = 0;

  return sh;
}

static void VLoopback_destroy(struct DriverInstance* sh)
{
  free(sh->dev_name);
  sh->dev_name = 0;

  if (sh->dev != -1)
    vl_close(sh->dev);
  sh->dev = -1;

  if (sh->data)
    free(sh->data);

  sh->data = 0;
  sh->data_size = 0;

  free(sh);
}

static int VLoopback_resize(struct DriverInstance* sh, int width, int height,
                            char* error_text, int text_len)
{ 
  // TODO: avoid close and open
  if (width != sh->width || height != sh->height)
    {
      if (sh->dev != -1)
        vl_close(sh->dev);

      sh->width  = width;
      sh->height = height;

      sh->dev = vl_open(sh->dev_name, error_text, text_len);

      if (sh->dev != -1)
        {
          return vl_init(sh->dev, width, height, error_text, text_len);
        }
    }
  return 1;
}

static int VLoopback_blit(struct DriverInstance* sh,
                          const unsigned char* fb,
                          int width, int height,
                          struct blit_params* params,
                          char* error_text, int text_len)
{
  unsigned char* framebuffer;

  // first scale and adjust input framebuffer fb
  int needs_adjust = (fabs(params->brightness-0.5) > EPS 
                      || fabs(params->contrast-1.0) > EPS
                      || fabs(params->gamma-1.0) > EPS
                      || params->invert);

  if (width != sh->width || height != sh->height
      || params->mirrorx || params->mirrory || needs_adjust)
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
      
      if (needs_adjust)
        {
          ls_set_adjustment(sh->pal, params->brightness, params->contrast,
                            params->gamma, params->invert);
                     
          ls_scale32m_adjust((uint_32*)sh->data, sh->width, sh->height,
                             (uint_32*)fb, width, height, params->mirrorx,
                             params->mirrory, sh->pal);
        }
      else
        {
          ls_scale32m((uint_32*)sh->data, sh->width, sh->height,
                      (uint_32*)fb, width, height, params->mirrorx,
                      params->mirrory);
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

      framebuffer = (unsigned char*) fb;
    }

  return vl_copy(sh->dev, framebuffer, sh->width, sh->height,
                 error_text, text_len);
}
