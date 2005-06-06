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

#include <string.h>

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

  /*vinfo_templ.red_mask   = 0x000000ff;
    vinfo_templ.green_mask = 0x0000ff00;
    vinfo_templ.blue_mask  = 0x00ff0000;
    vinfo_templ.bits_per_rgb  = 8;*/
  
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

int find_best_visual(Display* dpy,
                     XVisualInfo* chosen_vis)
{ 
  if (find_best_visual_bpp(dpy, chosen_vis, 24) == 0)
    return 0;
  else
    return find_best_visual_bpp(dpy, chosen_vis, 16);
}

 void convert_to_16_inplace(uint8_t* frb,
                            int width, int height)
{
  const uint8_t* src = frb;
  uint16_t* dst = (uint16_t*) frb;
  int i;

  for (i = width*height; i != 0; --i)
    {
      uint8_t b = src[0] >> 3;
      uint8_t g = src[1] >> 2;
      uint8_t r = src[2] >> 3;
      src += 4;

      *(dst++) = (r << 11) | (g << 5) | b;
    }
}

int big_endian()
{
  uint16_t tmp = 0xff11;

  uint8_t* p = (uint8_t*) &tmp;

  return p[0] == 0xff;
}

void convert_endianness(uint8_t* frb, int width, int height)
{
  uint8_t* ptr = frb;
  int i;

  for (i = width*height; i != 0; --i)
    {
      uint8_t b = ptr[0];
      uint8_t g = ptr[1];
      uint8_t r = ptr[2];
      uint8_t a = ptr[3];
      
      ptr[0] = a;
      ptr[1] = r;
      ptr[2] = g;
      ptr[3] = b;

      ptr += 4;
    }
}


/*
void print_visual(XVisualInfo* vinfo)
{
  printf("Visual %li: {\n", vinfo->visualid);
  printf("\tDepth\t\t: %i\n", vinfo->depth);
  printf("\tclass\t\t: %i\n", vinfo->class);
  printf("\tred_mask\t\t: %.8lx\n", vinfo->red_mask);
  printf("\tgreen_mask\t\t: %.8lx\n", vinfo->green_mask);
  printf("\tblue_mask\t\t: %.8lx\n", vinfo->blue_mask);
  printf("\tcolormap_size\t\t: %.8x\n", vinfo->colormap_size);
  printf("\tbits_per_rgb\t\t: %i\n", vinfo->bits_per_rgb);
  printf("}\n");
}*/



 int check_xshm_extension(Display* dpy/*, char* error_text, int text_len*/)
{
  const char* server_name = DisplayString(dpy);

  if (XShmQueryExtension(dpy) != True)
    {
      /*      snprintf(error_text, text_len,
              "XShm Extension not available for %s", server_name);*/
      return 0;
    }

  // XShmQueryExtension returns true whenever the xserver supports
  // this extension - but the connect will still fail if we are not on the
  // same machine!
  // Only if server_name_ptr has the form ":<server_nr>"
  // we assume that we are on the same machine.
  if (strlen(server_name) == 0 || server_name[0] != ':')
    {
      /*      snprintf(error_text, text_len, "Can't use shm driver on remote"
	       "displays\nUse ximage instead.\n"
	       "(If you want to use your local xserver, set DISPLAY to ':0'"
	       ", not 'localhost:0')");*/
       return 0;
    }

  return 1;
}

int check_xv_extension(Display* dpy)
{
  unsigned int version, release, request_base, event_base, error_base, ret;
  ret = XvQueryExtension(dpy,
                         &version,
                         &release,
                         &request_base,
                         &event_base,
                         &error_base);

  return (ret == Success);
}

