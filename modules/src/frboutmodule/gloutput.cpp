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

extern "C"
{
#include "gloutput.h"
#include "glutil.h" // dafuer gibts zwei implementierungen
#include "outputdriver.h"
}

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <stdint.h>
#include <stdexcept>
#include <memory>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define snprintf _snprintf
#include "multimonitor.h"
#endif

#include <GL/gl.h>

#define VERBOSE_GL_OUTPUT 1;

//-----------------------------------------------------------------------

struct DriverInstance 
{
  int        win_xsize;
  int        win_ysize;
  int        tex_xsize;
  int        tex_ysize;  
};

//-----------------------------------------------------------------------

static struct DriverInstance* GL_new_instance(const char* server_name,
					      int xpos, int ypos,
					      int width, int height,
					      int mmx_supported,
					      char* error_text, int buflen);

static void GL_destroy(struct DriverInstance* sh);

static int GL_resize(struct DriverInstance* sh,int width, int height,
		     char* error_text, int text_len);

static int GL_blit(struct DriverInstance* sh,
                    const unsigned char* fb, int width, int height,
		   struct blit_params* params,
                    char* error_text, int buflen);

//-----------------------------------------------------------------------

struct OutputDriver* GL_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));
  
  if (drv == 0)
    return 0;

  drv->new_instance  = GL_new_instance;
  drv->destroy       = GL_destroy;
  drv->resize        = GL_resize;
  drv->blit          = GL_blit;
  drv->window_pos    = 0;
  drv->frame         = 0;
  drv->always_on_top = 0;
  drv->to_monitor    = 0;

  drv->inst          = 0;
  return drv;
}

//-----------------------------------------------------------------------

static struct DriverInstance*
GL_new_instance(const char* server_name,
		int xpos, int ypos,
		int width, int height,int mmx_supported,
		char* error_text, int text_len)
{
#ifdef VERBOSE_GL_OUTPUT
  std::cout << "GL_new_instance: " << std::endl;
  std::cout << "server_name: \"" << server_name << "\"" << std::endl;
  std::cout << "xpos: " << xpos << std::endl;
  std::cout << "ypos: " << ypos << std::endl;
  std::cout << "width: " << width << std::endl;
  std::cout << "height: " << height << std::endl;
#endif
  try
    {
      std::auto_ptr<DriverInstance> sh(new DriverInstance);
      
      sh->win_xsize = width;
      sh->win_ysize = height;
      
      // resize texture lazy during blit. init with a minimum
      sh->tex_xsize = 1; 
      sh->tex_ysize = 1;
      
      if (!initOutput("Ge-Phex OpenGL Output Window",
		     server_name,sh->win_xsize, sh->win_ysize, 32))
	{
	  throw std::runtime_error("Could not initialize the GLOutput window!"); 
	}
      
      // print info about the OpenGL implementation
      
#ifdef VERBOSE_GL_OUTPUT
      std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
      std::cout << "Renderer:" << glGetString(GL_RENDERER)<< std::endl;
      std::cout << "Version: " << glGetString(GL_VERSION)<< std::endl;
      std::cout << "Extensions: " << glGetString(GL_EXTENSIONS)<< std::endl;
#endif
      
      glDisable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);
      glDisable(GL_CULL_FACE);
      
      glEnable(GL_TEXTURE_2D);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glClear(GL_COLOR_BUFFER_BIT);
      
      return sh.release();
    }
  catch (std::exception& e)
    {
      snprintf(error_text, text_len,e.what());
      return 0;
    }
  catch (...)
    {
      snprintf(error_text, text_len,"could not initialize GL output");
      return 0;
    }
}

static void GL_destroy(struct DriverInstance* sh)
{
  shutdownOutput();
  delete sh;
}

static int GL_resize(struct DriverInstance* sh, int width, int height,
                     char* error_text, int text_len)
{
  if (sh->win_xsize != width || sh->win_ysize != height)
    {
      sh->win_xsize = width;
      sh->win_ysize = height;
  
      glViewport(0, 0, sh->win_xsize, sh->win_ysize);
      resizeOutput(sh->win_xsize,sh->win_ysize);  
    }
  return 1;
}

static int GL_blit(struct DriverInstance* sh,
                   const unsigned char* fb,
                   int img_xsize, int img_ysize,
                   struct blit_params* params,
                   char* error_text, int buflen)
{
  double mirror_x;
  if (params->mirrorx)
    mirror_x=-1;
  else
    mirror_x=1;

  double mirror_y;
  if (params->mirrory)
    mirror_y=-1;
  else
    mirror_y=1;
    
  // update the base texturesize
  // calc the size to a pow of 2
  int new_tex_xsize=2;
  int new_tex_ysize=2;
  
  while (new_tex_xsize<img_xsize) new_tex_xsize*=2;
  while (new_tex_ysize<img_ysize) new_tex_ysize*=2;
  
  if ((new_tex_xsize!=sh->tex_xsize)||(new_tex_ysize!=sh->tex_ysize))
    {
      // alloc the texture
      char* buf =(char*)malloc(new_tex_xsize*new_tex_ysize*4);
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,new_tex_xsize,new_tex_ysize,
		   0,GL_BGRA,GL_UNSIGNED_BYTE,buf);
      free(buf);
    }

  sh->tex_xsize=new_tex_xsize;
  sh->tex_ysize=new_tex_ysize;
  
  // blit with texture
  glTexSubImage2D(GL_TEXTURE_2D,0,0,0,img_xsize,img_ysize,
		  GL_BGRA,GL_UNSIGNED_BYTE,fb);
  
  glBegin(GL_QUADS);
  glTexCoord2f(0,(double)img_ysize/(double)sh->tex_ysize);
  glVertex2f(-1*mirror_x,-1*mirror_y);
  
  glTexCoord2f(0,0);
  glVertex2f(-1*mirror_x,+1*mirror_y);
  
  glTexCoord2f((double)img_xsize/(double)sh->tex_xsize,0);
  glVertex2f(+1*mirror_x,+1*mirror_y);
  
  glTexCoord2f((double)img_xsize/(double)sh->tex_xsize,
	       (double)img_ysize/(double)sh->tex_ysize);
  glVertex2f(+1*mirror_x,-1*mirror_y);
  glEnd();

  glFinish();
  updateOutput(reinterpret_cast<const uint32_t*>(fb));
  return 1;
}

