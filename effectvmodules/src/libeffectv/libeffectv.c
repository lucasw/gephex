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

/**
 * Note: this library contains code from the EffecTV project!
 * http://effectv.sourceforge.net/
 * Their copyright applies for most parts.
 */

#include "libeffectv.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.1415
#endif

#include "EffecTV.h"
#include "utils.h"

#include "basic_types.h"

//--------------------------------------------------------------------------

int video_width                    = 320;
int video_height                   = 240;
int video_area                     = 320*240;
int screen_width                   = 320;
int screen_height                  = 240;
int screen_scale                   = 1; //TODO!!!
int stretch                        = 0;

//--------------------------------------------------------------------------

// shared buffer emulation
struct BufferNode
{
  void* data;
  struct BufferNode* next;
};

static struct BufferNode** s_sharedbuffer_head = 0;
static RGB32** s_background_ptr                = 0;
static unsigned char** s_diff_ptr              = 0;
static unsigned char** s_diff2_ptr             = 0;
static RGB32* s_screenaddress                  = 0;

//--------------------------------------------------------------------------

struct effectv_Effect
{
  effectv_lock_funcT   lock;
  effectv_unlock_funcT unlock;

  int width;
  int height;
  
  effectRegistFunc* register_func;
  effect* effect;

  RGB32* background;
  unsigned char* diff;
  unsigned char* diff2;

  struct BufferNode* sharedbuffer_head;

  unsigned char* scaled_src;
  unsigned char* scaled_dst;
  int scaled_size;
};

//--------------------------------------------------------------------------

void fb_scale32(uint_32* dst, int dwidth, int dheight,
                const uint_32* src, int swidth, int sheight)
{
  if (dwidth == swidth && dheight == sheight)
    {
      memcpy(dst, src, sizeof(*dst)*dwidth*dheight);
    }
  else
    {
  
      int y;
      uint_32 x_a, y_a;
      uint_32 A,B;
      double deltax=.0, deltay=.0;

      assert (dwidth >= 0 && dheight >= 0);

      deltax = (double)swidth  / (double)dwidth;
      deltay = (double)sheight / (double)dheight;

      A = (uint_32) (65536.*deltax);
      B = (uint_32) (65536.*deltay);

      y_a = 0;

      for (y = dheight; y > 0; --y)
        {
          int x;
          const uint_32* line_base = src + ((y_a >> 16) * swidth);
          x_a = 0;		
          for (x = dwidth; x > 0; --x)
            {			
              *dst= line_base[x_a >> 16];
              ++dst;
              x_a += A;
            }
          y_a += B;
        }
    }
}

//--------------------------------------------------------------------------

struct effectv_Effect* effectv_init(void* e,
                                    effectv_lock_funcT lock_func,
                                    effectv_unlock_funcT unlock_func)
{
  int error;
  struct effectv_Effect* self = malloc(sizeof(*self));

  self->lock              = lock_func;
  self->unlock            = unlock_func;
  self->width             = video_width;
  self->height            = video_height;

  self->scaled_src        = 0;
  self->scaled_dst        = 0;
  self->scaled_size       = 0;

  s_background_ptr        = &self->background;
  s_diff_ptr              = &self->diff;
  s_diff2_ptr             = &self->diff2;
  s_sharedbuffer_head     = &self->sharedbuffer_head;

  self->background        = 0;
  self->diff              = 0;
  self->diff2             = 0;
  self->sharedbuffer_head = 0;

  image_init();
  yuv_init();

  self->register_func = (effectRegistFunc*) e;
  self->effect        = self->register_func();
  //printf("name = %s\n", self->effect->name);
  error = self->effect->start();
  if (error)
    {
      fprintf(stderr, "Error at start()!\n");
      image_end();
      free(self);
      return 0;
    }
  //printf("...started\n");
  return self;
}

//--------------------------------------------------------------------------

int effectv_draw(struct effectv_Effect* self,
                 unsigned char* vid, unsigned char* screen,
                 int width, int height)

{
  unsigned char* source;
  unsigned char* dest;
  int source_width;
  int source_height;

  if (self->lock)
    self->lock();

  s_background_ptr    = &self->background;
  s_diff_ptr          = &self->diff;
  s_diff2_ptr         = &self->diff2;
  s_sharedbuffer_head = &self->sharedbuffer_head;

  if (width < 320 || height < 240)
    {
      // need to scale
      int new_width  = 320;
      int new_height = 240;
      int size       = new_width * new_height * 4;

      if (self->scaled_src != 0 && self->scaled_size < size)
        {
          free(self->scaled_src);
          free(self->scaled_dst);
          self->scaled_src = 0;
          self->scaled_dst = 0;
        }

      if (self->scaled_src == 0)
        {
          self->scaled_size = size;
          self->scaled_src  = malloc(size);
          self->scaled_dst  = malloc(size);
        }

      assert(self->scaled_size >= size);
      assert(self->scaled_src && self->scaled_dst);

      fb_scale32((uint_32*) self->scaled_src,
                 new_width, new_height,
                 (uint_32*) vid,
                 width, height);

      source        = self->scaled_src;
      dest          = self->scaled_dst;
      source_width  = new_width;
      source_height = new_height;
    }
  else
    {
      // did not need to scale
      if (self->scaled_src)
        {
          free(self->scaled_src);
          free(self->scaled_dst);
          self->scaled_src  = 0;
          self->scaled_dst  = 0;
          self->scaled_size = 0;
        }
      source        = vid;
      dest          = screen;
      source_width  = width;
      source_height = height;
    }

  video_width      = source_width;
  video_height     = source_height;
  screen_width     = video_width;
  screen_height    = video_height;
  video_area       = video_height*video_width;

  s_screenaddress  = (RGB32*) dest;

  assert(source != 0 && dest != 0);
  assert(video_width >= 320 && video_height >= 240);

  if (video_width  != self->width ||
      video_height != self->height)
    {
      int error;
      self->effect->stop();

      image_end();
      image_init();

      sharedbuffer_end();

      free(self->effect);
      self->effect = self->register_func();
      error = self->effect->start();
      if (error)
        {
          fprintf(stderr, "Error at restart()!\n");
          //          image_end();
          //          free(self);
          if (self->unlock)
            self->unlock();
          return 1;
        }

      self->width  = video_width;
      self->height = video_height;
    }

  assert(self->width == video_width);
  assert(self->height == video_height);

  self->effect->draw((RGB32*) source, (RGB32*) dest);

  if (width != screen_width || height != screen_height)
    {
      assert(self->scaled_dst);
      assert(self->scaled_size >= screen_width*screen_height*4);
      // if it has been scaled before, the result must be scaled down again
      fb_scale32((uint_32*) screen, width, height,
                 (uint_32*) self->scaled_dst, screen_width, screen_height);
    }
  else
  {
    assert(self->scaled_src == 0 &&
           self->scaled_dst == 0);
  }

  if (self->unlock)
    self->unlock();

  return 0;
}

//--------------------------------------------------------------------------

void effectv_teardown(struct effectv_Effect* self)
{  
  s_background_ptr    = &self->background;
  s_diff_ptr          = &self->diff;
  s_diff2_ptr         = &self->diff2;
  s_sharedbuffer_head = &self->sharedbuffer_head;

  self->effect->stop();
  free(self->effect);

  sharedbuffer_end();
  image_end();

  if (self->scaled_src)
    {
      free(self->scaled_src);
      free(self->scaled_dst);
      self->scaled_src  = 0;
      self->scaled_dst  = 0;
      self->scaled_size = 0;
    }

  self->effect        = 0;
  self->register_func = 0;
  free(self);
}

//--------------------------------------------------------------------------

#if defined(OS_WIN32)
void bzero(void* ptr, int size)
{
  memset(ptr, 0, size);
}
#endif

/**
 * Helper functions
 */

/**********************************************************************/

/**
 * Emulator functions for effectv
 */
int sharedbuffer_init() {
  return 0;
}


void sharedbuffer_end()
{
  struct BufferNode* current = *s_sharedbuffer_head;

  while (current != 0)
    {
      struct BufferNode* next = current->next;
      free(current->data);
      free(current);      
      current = next;
    }

  *s_sharedbuffer_head = 0;
}

void sharedbuffer_reset()
{
  sharedbuffer_end();
}

unsigned char *sharedbuffer_alloc(int size)
{
  struct BufferNode** current = s_sharedbuffer_head;
  struct BufferNode* tail = 0;

  while(*current != 0)
    {
      tail = *current;
      current = &((*current)->next);
    }

  *current = malloc(sizeof(struct BufferNode));
  (*current)->data = malloc(size);
  (*current)->next = 0;

  if (tail)
    tail->next = *current;
  
  return (*current)->data;

  //  return malloc(size);
}


//void image_stretching_buffer_clear(RGB32 color) {}
void image_stretch_to_screen() {}
void image_stretch(RGB32 *i, int a, int b, RGB32 *u, int c, int d) {};

RGB32* screen_getaddress()
{
  return s_screenaddress;
}

/***************************************************************************
 *
 * NOTE: code below this point is taken from EffecTV release 0.3.8, 
 * file utils.c.
 *
 * Some minor modifications have been done to make sure it works with GePhex.
 *
 * Updated to incorporate changes from 0.3.9
 *
 ***************************************************************************/

/*
 * fastrand - fast fake random number generator
 * Warning: The low-order bits of numbers generated by fastrand()
 *          are bad as random numbers. For example, fastrand()%4
 *          generates 1,2,3,0,1,2,3,0...
 *          You should use high-order bits.
 */
unsigned int fastrand_val;

unsigned int fastrand()
{
	return (fastrand_val=fastrand_val*1103515245+12345);
}

void fastsrand(unsigned int seed)
{
	fastrand_val = seed;
}

/*
 * HSI color system utilities
 */
static int saturate(double f)
{
	int i;

	i=(int)f;
	if(i<0)i=0;
	if(i>255)i=255;
	return i;
}

void HSItoRGB(double H, double S, double I, int *r, int *g, int *b)
{
	double T,Rv,Gv,Bv;

	T=H;
	Rv=1+S*sin(T-2*M_PI/3);
	Gv=1+S*sin(T);
	Bv=1+S*sin(T+2*M_PI/3);
	T=255.999*I/2;
	*r=saturate(Rv*T);
	*g=saturate(Gv*T);
	*b=saturate(Bv*T);
}

/* We don't want no leaks */
void image_end()
{
  //  printf("image_end() called\n");
  if ((*s_background_ptr))
    {
      free((*s_background_ptr));
      *s_background_ptr = 0;
    }

  if ((*s_diff_ptr))
    {
      free((*s_diff_ptr));
      *s_diff_ptr = 0;
    }

  if ((*s_diff2_ptr))
    {
      free((*s_diff2_ptr));
      *s_diff2_ptr = 0;
    }
}

int image_init()
{
  //  printf("image_init() called, video_area=%i!\n", video_area);
  //	stretching_buffer = (RGB32 *)malloc(video_area*sizeof(RGB32));
  (*s_background_ptr) = (RGB32 *)malloc(video_area*sizeof(RGB32));
  (*s_diff_ptr) = (unsigned char *)malloc(video_area*sizeof(unsigned char));
  (*s_diff2_ptr) = (unsigned char *)malloc(video_area*sizeof(unsigned char));
	//	if(stretching_buffer == NULL || (*s_background_ptr) == NULL || (*s_diff_ptr) == NULL || (*s_diff2_ptr) == NULL) {
	//		return -1;
	//	}
  memset((*s_diff2_ptr),0, video_area*sizeof(unsigned char));

  return 0;
}

// ----------- from image.c

/*
 * Collection of background subtraction functions
 */

/* checks only fake-Y value */
/* In these function Y value is treated as R*2+G*4+B. */

static int y_threshold;
void image_set_threshold_y(int threshold)
{
  y_threshold = threshold * 7; /* fake-Y value is timed by 7 */
}

void image_bgset_y(RGB32 *src)
{
	int i;
	int R, G, B;
	RGB32 *p;
	short *q;

	if (!src)
	  return;

	p = src;
	q = (short *)(*s_background_ptr);
	for(i=0; i<video_area; i++) {
		R = ((*p)&0xff0000)>>(16-1);
		G = ((*p)&0xff00)>>(8-2);
		B = (*p)&0xff;
		*q = (short)(R + G + B);
		p++;
		q++;
	}
}

unsigned char *image_bgsubtract_y(RGB32 *src)
{
	int i;
	int R, G, B;
	RGB32 *p;
	short *q;
	unsigned char *r;
	int v;

	p = src;
	q = (short *)(*s_background_ptr);
	r = (*s_diff_ptr);
	for(i=0; i<video_area; i++) {
		R = ((*p)&0xff0000)>>(16-1);
		G = ((*p)&0xff00)>>(8-2);
		B = (*p)&0xff;
		v = (R + G + B) - (int)(*q);
		*r = ((v + y_threshold)>>24) | ((y_threshold - v)>>24);

		p++;
		q++;
		r++;
	}

	return (*s_diff_ptr);
/* The origin of subtraction function is;
 * diff(src, dest) = (abs(src - dest) > threshold) ? 0xff : 0;
 *
 * This functions is transformed to;
 * (threshold > (src - dest) > -threshold) ? 0 : 0xff;
 *
 * (v + threshold)>>24 is 0xff when v is less than -threshold.
 * (v - threshold)>>24 is 0xff when v is less than threshold.
 * So, ((v + threshold)>>24) | ((threshold - v)>>24) will become 0xff when
 * abs(src - dest) > threshold.
 */
}

/* Background image is refreshed every frame */
unsigned char *image_bgsubtract_update_y(RGB32 *src)
{
	int i;
	int R, G, B;
	RGB32 *p;
	short *q;
	unsigned char *r;
	int v;

	p = src;
	q = (short *)(*s_background_ptr);
	r = (*s_diff_ptr);
	for(i=0; i<video_area; i++) {
		R = ((*p)&0xff0000)>>(16-1);
		G = ((*p)&0xff00)>>(8-2);
		B = (*p)&0xff;
		v = (R + G + B) - (int)(*q);
		*q = (short)(R + G + B);
		*r = ((v + y_threshold)>>24) | ((y_threshold - v)>>24);

		p++;
		q++;
		r++;
	}

	return (*s_diff_ptr);
}

/* noise filter for subtracted image. */
unsigned char *image_diff_filter(unsigned char *diff)
{
	int x, y;
	unsigned char *src, *dest;
	unsigned int count;
	unsigned int sum1, sum2, sum3;
	const int width = video_width;

	src = diff;
	dest = (*s_diff2_ptr) + width +1;
	for(y=1; y<video_height-1; y++) {
		sum1 = src[0] + src[width] + src[width*2];
		sum2 = src[1] + src[width+1] + src[width*2+1];
		src += 2;
		for(x=1; x<width-1; x++) {
			sum3 = src[0] + src[width] + src[width*2];
			count = sum1 + sum2 + sum3;
			sum1 = sum2;
			sum2 = sum3;
			*dest++ = (0xff*3 - count)>>24;
			src++;
		}
		dest += 2;
	}
	
	return (*s_diff2_ptr);
}


/* Y value filters */
unsigned char *image_y_over(RGB32 *src)
{
	int i;
	int R, G, B, v;
	unsigned char *p = (*s_diff_ptr);

	for(i = video_area; i>0; i--) {
		R = ((*src)&0xff0000)>>(16-1);
		G = ((*src)&0xff00)>>(8-2);
		B = (*src)&0xff;
		v = y_threshold - (R + G + B);
		*p = (unsigned char)(v>>24);
		src++;
		p++;
	}

	return (*s_diff_ptr);
}

unsigned char *image_y_under(RGB32 *src)
{
	int i;
	int R, G, B, v;
	unsigned char *p = (*s_diff_ptr);

	for(i = video_area; i>0; i--) {
		R = ((*src)&0xff0000)>>(16-1);
		G = ((*src)&0xff00)>>(8-2);
		B = (*src)&0xff;
		v = (R + G + B) - y_threshold;
		*p = (unsigned char)(v>>24);
		src++;
		p++;
	}

	return (*s_diff_ptr);
}



/*
 * from yuv.c--------------------------------------------------------
 */

int YtoRGB[256];
int VtoR[256], VtoG[256];
int UtoG[256], UtoB[256];
int RtoY[256], RtoU[256], RtoV[256];
int GtoY[256], GtoU[256], GtoV[256];
int BtoY[256],            BtoV[256];

int yuv_init()
{
	static int initialized = 0;
	int i;

	if(!initialized) {
		for(i=0; i<256; i++) {
			YtoRGB[i] =  1.164*(i-16);
			VtoR[i] =  1.596*(i-128);
			VtoG[i] = -0.813*(i-128);
			UtoG[i] = -0.391*(i-128);
			UtoB[i] =  2.018*(i-128);
			RtoY[i] =  0.257*i;
			RtoU[i] = -0.148*i;
			RtoV[i] =  0.439*i;
			GtoY[i] =  0.504*i;
			GtoU[i] = -0.291*i;
			GtoV[i] = -0.368*i;
			BtoY[i] =  0.098*i;
			BtoV[i] = -0.071*i;
		}
		initialized = 1;
	}
	return 0;
}

//--------------------------------------------------------------------------
