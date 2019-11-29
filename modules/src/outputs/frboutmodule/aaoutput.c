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

#include "aaoutput.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "aalib.h"

#include "outputdriver.h"

#include "basic_types.h"

struct DriverInstance {
  aa_context* context;
};

static struct DriverInstance* 
AA_new_instance(const char* server_name,
                int xpos, int ypos,
                int width, int height, int mmx_supported,
                char* error_text, int buflen);

static void AA_destroy(struct DriverInstance* sh);

static int  AA_resize(struct DriverInstance* sh,
                          int width, int height,
                          char* error_text, int text_len);

static int  AA_blit(struct DriverInstance* sh,
                        const unsigned char* fb,
                        int width, int height,
                        struct blit_params* params,
                        char* error_text, int buflen);

static int scale_grey(uint_8* result, const uint_32* data, int_32 width,
                      int_32 height, int_32 newWidth, int_32 newHeight,
                      int mirrorx, int mirrory);
/***************************************************************************/

struct OutputDriver* AA_get_driver()
{
  struct OutputDriver* drv = (struct OutputDriver*) malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->new_instance  = AA_new_instance;
  drv->destroy       = AA_destroy;
  drv->resize        = AA_resize;
  drv->blit          = AA_blit;
  drv->window_pos    = 0;
  drv->frame         = 0;
  drv->always_on_top = 0;
  drv->to_monitor    = 0;


  drv->inst          = 0;
  return drv;
}

/***************************************************************************/

static aa_context* init_aa_context(int width, int height)
{
  struct aa_hardware_params params;
  double wf = 1./8., hf = 1./8.;
  int w_error, h_error;
  struct aa_context* c;

  memset(&params, 0, sizeof(params));
  params.supported = AA_EXTENDED | AA_NORMAL_MASK | AA_DIM_MASK
    | AA_BOLD_MASK | AA_BOLDFONT_MASK | AA_REVERSE_MASK;
  
  /*  while(1)
    {
      params.width   = width * hf;
      params.height  = height * wf;

      c = aa_autoinit(&params);

      w_error =  width - aa_imgwidth(c);
      h_error =  height - aa_imgheight(c);
      
      if (abs(w_error) < 4 && abs(h_error) < 4)
        break;
      
      if (w_error < 0)
        wf *= 0.99;
      else if (w_error > 0)
        wf *= 1.01;

      if (h_error < 0)
        hf *= 0.99;
      else if (h_error > 0)
        hf *= 1.01;

      printf("w = %i, iw = %i, w_e = %i, wf=%f\n", width, aa_imgwidth(c),
             w_error, wf);
      printf("h = %i, ih = %i, h_e = %i, hf=%f\n", height, aa_imgheight(c),
             h_error, hf);

      aa_close(c);
      //      wf = (double) aa_imgwidth(c) / (double) width;        
      //      hf = (double) aa_imgheight(c) / (double) height;

      }*/

  return aa_autoinit(&params);
}

static void my_handler(struct aa_context* context)
{
  printf("resize handler\n");
  aa_resize(context);
}

static struct DriverInstance*
AA_new_instance(const char* server_name,
                    int xpos, int ypos,
                    int width, int height, int mmx_supported,
                    char* error_text, int textlen)
{
  struct DriverInstance* sh = (struct DriverInstance*) malloc(sizeof(*sh));
 
  sh->context = init_aa_context(width, height);

  if (sh->context == 0)
    {
      snprintf(error_text, textlen, "Could not get aa context");
      free(sh);
      return 0;
    }

  // TODO: seems not to work
  aa_resizehandler(sh->context, (void *)my_handler);

  return sh;
}

static void AA_destroy(struct DriverInstance* sh)
{
  aa_close(sh->context);
  free(sh);
}

static int AA_resize(struct DriverInstance* sh, int width, int height,
                     char* error_text, int text_len)
{ 
  //TODO
  /*  aa_context* new_context  = init_aa_context(width, height);

  if (sh->context == 0)
    {
      snprintf(error_text, text_len, "Could not get aa context");
      return 0;
    }
  else
    {
      int aa_width  = aa_imgwidth(new_context);
      int aa_height = aa_imgheight(new_context);

      printf("w = %i, h = %i\n", aa_width, aa_height);
      aa_close(sh->context);
      sh->context = new_context;

      return 1;
      }*/
  return 1;
}

static int AA_blit(struct DriverInstance* sh,
                   const unsigned char* fb,
                   int width, int height,
                   struct blit_params* params,
                   char* error_text, int textlen)
{
  unsigned char* img_mem;
  int aa_width;
  int aa_height;
  struct aa_renderparams render_params;

  // TODO: no good
  aa_resize(sh->context);

  img_mem = aa_image(sh->context);
  if (img_mem == 0)
    {
      snprintf(error_text, textlen, "No Image mem!");
      return 0;
    }

  aa_width  = aa_imgwidth(sh->context);
  aa_height = aa_imgheight(sh->context);

  scale_grey(img_mem, (uint_32*) fb, width, height, aa_width, aa_height,
             params->mirrorx, params->mirrory);

  render_params.bright    = (int) (params->brightness * 255.*2.);
  render_params.bright   -= 255;
  render_params.contrast  = (int) (params->contrast * 127.*0.25);
  render_params.gamma     = (float) params->gamma;
  render_params.inversion = 0;
  render_params.dither    = AA_FLOYD_S;
  render_params.randomval = 0;
  render_params.inversion = params->invert;

  aa_render(sh->context, &render_params, 0, 0, 
            aa_scrwidth(sh->context),
            aa_scrheight(sh->context));

  aa_flush(sh->context);
  return 1;
}

/***************************************************************************/

static uint_8 grey_value(uint_32 color)
{
  unsigned char* tmpc = (uint_8*)&color;
  return (uint_8) ((tmpc[0] + tmpc[1] + tmpc[2]) / 3);
}

static int scale_grey(uint_8* result, const uint_32* data, int_32 width,
                      int_32 height, int_32 newWidth, int_32 newHeight,
                      int mirrorx, int mirrory)
{	
  int_32 x,y;
  double alpha = (double) width / (double) newWidth;
  double beta = (double) height / (double) newHeight;
  uint_32 A = (int_32) (alpha* (1<<16));
  uint_32 B = (int_32) (beta* (1<<16));
  int dirx, diry;
  int_32 bb;

  uint_8* current = result;

  if (mirrorx)
    {
      dirx = -1;
      current += newWidth;
    }
  else
    {
      dirx = 1;
    }

  if (mirrory)
    {
      diry = -newWidth;
      current += (newHeight-1)*newWidth;
    }
  else
    {
      diry = newWidth;
    }

  bb = 0;
  for (y = 0; y < newHeight; ++y)
    {			
      int_32 aa = 0;			
      const uint_32* offset = data + (int) (bb >> 16) * width;
      uint_8* cx = current;
      for (x = 0; x < newWidth; ++x)
        {	
          *cx = grey_value(offset[aa >> 16]);
          aa += A;
          cx += dirx;
        }
      bb += B;
      current += diry;
    }

  return 1;
}
