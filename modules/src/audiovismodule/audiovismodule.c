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

#include "audiovismodule.h"

#include <math.h>

static logT s_log;

#define NUM_BINS 64

static const int BORDER = 2;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));


  return my;
}

void destruct(MyInstance* my)
{

  free(my);
}

void get_ampls(double* dst, const double* src, int n) {
  int i;

  for (i = 0; i < n; ++i)
    {
      double re = src[2*i];
      double im = src[2*i+1];
      dst[i] = sqrt(re*re + im*im);
    }
}

void get_bins(double* bins, int n_bins, const double* ampls, int n_ampls)
{
  int step = n_ampls / n_bins;
  int i, j;

  for (i = 0; i < n_bins; ++i)
    {
      double s = 0;
      for (j = i*step; j < (i+1)*step; ++j)
        {
          s += ampls[j];
        }
      bins[i] = s;
    }
}


void draw_hline(int_32* fb, int y, int x0, int x1, int_32 col)
{
  int x;
  int offset = (479-y)*640;

  for (x = x0; x < x1; ++x)
    fb[offset+x] = col;
}
void draw_box(int_32* fb, int x0, int y0, int x1, int y1, int_32 col)
{
  int y;
  for (y = y0; y <= y1; ++y)
    {
      draw_hline(fb, y, x0, x1, col);
    }
}

void draw_bins(int_32* fb, double* bins, int n_bins)
{
  int width = 640 / n_bins - BORDER;
  int i, x, y;

  for (i = 0; i < n_bins; ++i)
    {
      y = (int) (bins[i]*480);
      if (y < 0) y = 0;
      if (y >= 480) y = 479;
      x = i*(width + BORDER);
      draw_box(fb, x, 0, x+width, y, 0xffffffff);
    }
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  {
    FrameBufferAttributes attr;
    attr.xsize = 640;
    attr.ysize = 480;
    framebuffer_changeAttributes(inst->out_r, &attr);
  }

  {
    int len = inst->in_audio->len;
    double* ampl = malloc(len/2 * sizeof(double));
    double bins[NUM_BINS];

    assert(inst->in_audio->channels == 1);

    get_ampls(ampl, inst->in_audio->samples, len/2);
    get_bins(bins, NUM_BINS, ampl, len/2);
    free(ampl);

    memset(inst->out_r->framebuffer, 0, 640*480*4);
    draw_bins(inst->out_r->framebuffer, bins, NUM_BINS);
  }
 
}


