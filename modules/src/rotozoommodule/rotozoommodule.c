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

#include "rotozoommodule.h"

#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

#include "libgeo.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif

#define FIXEDPNT_SCALE 65536

#if defined(_MSC_VER)
#define lrint(a) ((long int) a)
#endif

__inline int_32 cvt_to_fp(double a)
{
  return (int_32) lrint(FIXEDPNT_SCALE * a);
}

const int ROTOZOOM_SAFETY_BORDER = 5;

/**
 * Describes an affine-linear transformation
 *
 * /   \     /        \      /   \      /    \
 * | u |  -  | AX  BY |  \/  | x |  _|_ | TX |
 * | v |  -  | BX  AY |  /\  | y |   |  | TY |
 * \   /     \        /      \   /      \    /
 */
struct ALTransform {
  double AX, AY, BX, BY;
  double Tx, Ty;
};

struct ALTransformFP {
  int_32 AX, AY, BX, BY;
  int_32 Tx, Ty;
};

struct input_params_t {
  double zoom;
  double theta;
  int transpx;
  int transpy;
  int xsize_src;
  int ysize_src;
  int xsize_result;
  int ysize_result;
};

/**
 * 
 */
static void inverse_transform(struct geo_Point* dst, int x, int y,
			      const struct ALTransform* trans)
{
  double x_ = x - trans->Tx;
  double y_ = y - trans->Ty;
  dst->x = trans->AX * x_ + trans->BY * y_;
  dst->y = trans->BX * x_ + trans->AY * y_;
}

static void build_transform(struct ALTransform* trans,
                            const struct input_params_t* p)
{
  double xs, ys;
  double a, b;
  
  xs = (p->xsize_src / (double) p->xsize_result) * p->zoom;
  ys = (p->ysize_src / (double) p->ysize_result) * p->zoom;
  a  =  cos(p->theta);
  trans->AX = xs * a;
  trans->AY = ys * a;
  b = sin(p->theta);
  trans->BX = xs * b;
  trans->BY = -ys * b;

  trans->Tx = (-(p->xsize_src/2)-p->transpx)*trans->AX
    - ((p->ysize_src/2)+p->transpy)*trans->BY + (p->xsize_src/2);
  trans->Ty = (-(p->xsize_src/2)-p->transpx)*trans->BX
    - ((p->ysize_src/2)+p->transpy)*trans->AY + (p->ysize_src/2);
}

/**
 * Creates the Transformation and its inverse.
 */
static void build_transforms(struct ALTransform* trans,
			     struct ALTransform* transi,
                             const struct input_params_t* p)

{
  double xs, ys;
  double a, b;
  
  build_transform(trans, p);

  // build inverse transform
  xs = (p->xsize_src / (double) p->xsize_result) * p->zoom;
  ys = (p->ysize_src / (double) p->ysize_result) * p->zoom;
  a  = cos(p->theta);
  b  = sin(p->theta);


  transi->AX =  a / xs;
  transi->AY =  a / ys;
  transi->BX = -b / ys;
  transi->BY =  b / xs;
  transi->Tx = trans->Tx;
  transi->Ty = trans->Ty;
}

/**
 * Applies the inverse transformation to the src rectangle and clips
 * the result with the result rectangle.
 * The resulting polygon will be stored in points.
 * points must have place for at least 8 points.
 * *num_points contains the number of corners of points.
 *
 * Returns >0 if there is a positive intersection,
 * 0 if the clipped poly is empty.
 * If the clipped poly equals the result-rectangle, 2 is returned
 */
static int transform_and_clip(struct ALTransform* transi,
			      int xsize_src, int ysize_src,
			      int xsize_result, int ysize_result,
			      struct geo_Point* points, int *num_points,
			      int border)
{
  struct geo_Point points_screen[4];
  struct geo_Point points_transformed[4];
  int ok;

  inverse_transform(points_transformed + 0, border, border,
		    transi);
  inverse_transform(points_transformed + 1, border, ysize_src-1-border,
		    transi);
  inverse_transform(points_transformed + 2, xsize_src-1-border,
		    ysize_src-1-border,
		    transi);
  inverse_transform(points_transformed + 3, xsize_src-1-border, border,
		    transi);

  points_screen[0].x =         0;
  points_screen[0].y =         0;
  points_screen[1].x =         0;
  points_screen[1].y = (ysize_result-1);
  points_screen[2].x = (xsize_result-1);
  points_screen[2].y = (ysize_result-1);
  points_screen[3].x = (xsize_result-1);
  points_screen[3].y =         0;

  ok = geo_intersect_polygons(points, num_points,
			      points_transformed, 4,
			      points_screen, 4);

  if (ok > 0)
    {
      if (poly_equals(points, *num_points, points_screen, 4, 0.0001))
	return 2;
      
      return 1;
    }
  return 0;
}


static void poly_print(struct geo_Point* pi, int num_points)
{
  int i;
  for (i = 0; i < num_points; ++i) {
    printf("pi_%i = (%f, %f)\n", i, pi[i].x , pi[i].y );
  }
}

typedef void (*rotozoomT)(const struct input_params_t* p,
			  uint_32* src, uint_32* result, void*);

static void rotozoom1(const struct input_params_t* p,
                      uint_32* src, uint_32* result, void*);

static void rotozoom_mirror(const struct input_params_t* p,
                            uint_32* src, uint_32* result, void*);

static void rotozoom2(const struct input_params_t* p,
                      uint_32* src, uint_32* result, void*);


#if defined(M_PI)
#undef M_PI
#endif

static logT s_log;

const double M_PI = 3.1415926535897932384626433832795;

/****************************************************************************/

struct ScanLine {
  int x1;
  int x2;
  int_32 x_a;
  int_32 x_b;
};

struct EdgeBuffer {
  int yres;
  struct ScanLine* scanlines;
};

typedef struct _MyInstance {

  rotozoomT rotozoom;
  struct EdgeBuffer edges;
  int usesEdgeBuffer;

  StringType oldRoutine;

  int back_needed;
  int text_needed;

} MyInstance, *MyInstancePtr;

int init(logT does_not_matter)
{
  s_log = does_not_matter;
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->rotozoom = 0;
  my->usesEdgeBuffer = 0;

  my->edges.yres = 0;
  my->edges.scanlines = 0;

  my->back_needed = 1;
  my->text_needed = 1;

  string_initInstance(&my->oldRoutine);
  return my;
}

void destruct(MyInstance* my)
{
  string_destroyInstance(&my->oldRoutine);
  free(my);
}


void calc_parameters(void* instance, struct input_params_t* p)
{
  InstancePtr inst = (InstancePtr) instance;  

  p->xsize_src    = inst->in_texture->xsize;
  p->ysize_src    = inst->in_texture->ysize;
  p->xsize_result = inst->in_texture->xsize;
  p->ysize_result = inst->in_texture->ysize;

  p->theta = fmod((M_PI * inst->in_rot->number) / 180, 2*M_PI);
  p->zoom =  trim_double(inst->in_zoom->number,0.001,8);

  p->transpx = (int) ((3*p->xsize_result*trim_double(inst->in_disp->x,0,1))
                      -(p->xsize_result*1.5));

  p->transpy = (int) ((3*p->ysize_result*trim_double(inst->in_disp->y,0,1))
                      -(p->ysize_result*1.5));
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  struct geo_Point points[8];
  int num_points;
  int ok;
  struct ALTransform trans, transi;
  // safety border for the inverse transformation
  const int border = ROTOZOOM_SAFETY_BORDER;

  struct input_params_t p;

  MyInstancePtr my = inst->my;

  my->text_needed = 1;
  my->back_needed = 1;

  if (strcmp("mirror", inst->in_routine->text) == 0)
    {
      neededInputs[in_background] = 0;
      my->back_needed = 0;
    }
  else
    {
      calc_parameters(inst, &p);

      // calculate the transformation and the inverse transformation
      build_transforms(&trans, &transi, &p);

      ok = transform_and_clip(&transi, p.xsize_src, p.ysize_src,
                              p.xsize_result, p.ysize_result,
                              points, &num_points, border);

      if (ok == 0)
        {
          my->text_needed = 0;
          neededInputs[in_texture] = 0;
        }
      else if (ok == 2)
        {
          my->back_needed = 0;
          neededInputs[in_background] = 0;
        }
    }

}

static int no_zoom_and_no_rotation_and_no_transp(const struct input_params_t*p)
{
  return (p->transpx == 0) && (p->transpy == 0)
    && (fabs(p->theta) < 0.0000001 || fabs(p->theta - 2*M_PI) < 0.0000001)
    && (fabs(p->zoom - 1.0) < 0.00001);
}

void patchLayout(Instance* inst, int out2in[])
{
  struct input_params_t p;

  calc_parameters(inst, &p);

  if (no_zoom_and_no_rotation_and_no_transp(&p))
    {
      out2in[out_r] = in_texture;
    }
  else if (!trim_bool(inst->in_copy_background->number))
    {
      out2in[out_r] = in_background;
    }
}

/****************************************************************************/

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  struct input_params_t p;

  int copy_background = trim_bool(inst->in_copy_background->number);
  calc_parameters(instance, &p);

  if (strcmp(my->oldRoutine.text, inst->in_routine->text) != 0)
    {
      string_assign(&my->oldRoutine, inst->in_routine);

      if (strcmp(my->oldRoutine.text, "regular") == 0)
	{
	  s_log(2, "Using regular rotozooming");
	  my->rotozoom = rotozoom1;
	  my->usesEdgeBuffer = 0;
	}
      else if (strcmp(my->oldRoutine.text, "poly") == 0)
	{
	  s_log(2, "Using poly rotozooming");
	  my->rotozoom = rotozoom2;
	  my->usesEdgeBuffer = 1;
	}
      else if (strcmp(my->oldRoutine.text, "mirror") == 0)
	{
	  s_log(2, "Using mirror rotozooming");
	  my->rotozoom = rotozoom_mirror;
	  my->usesEdgeBuffer = 0;
	}
      else
	{
	  char buffer[128];
	  snprintf(buffer, sizeof(buffer),
		   "Unsupported rotozoom routine: '%s', "
		   "using 'regular' instead",
		   my->oldRoutine.text);

	  s_log(0, buffer);
	  my->rotozoom = rotozoom1;
	  my->usesEdgeBuffer = 0;
	}
    }

  if (no_zoom_and_no_rotation_and_no_transp(&p))
    return;

  if (my->usesEdgeBuffer && my->edges.yres != p.ysize_result)
    {
      if (my->edges.scanlines != 0)
	free(my->edges.scanlines);

      my->edges.scanlines = (struct ScanLine*) 
        malloc(sizeof(*(my->edges.scanlines))* p.ysize_result);
      my->edges.yres = p.ysize_result;
    }

  if (copy_background && my->back_needed)
    {
      framebuffer_assign(inst->out_r, inst->in_background);
    }

  {
    FrameBufferAttributes attribs;
    attribs.xsize = p.xsize_src;
    attribs.ysize = p.ysize_src;
    framebuffer_changeAttributes(inst->out_r, &attribs);
  }

  if (my->text_needed)
    {
      my->rotozoom(&p, inst->in_texture->framebuffer,
		   inst->out_r->framebuffer, &my->edges);
    }
}

/****************************************************************************/

static void build_fixedpoint_transform(struct ALTransformFP* tr,
                                       const struct input_params_t* p)
{
  struct ALTransform trans;
  build_transform(&trans, p);

  tr->AX = cvt_to_fp(trans.AX);
  tr->AY = cvt_to_fp(trans.AY);
  tr->BX = cvt_to_fp(trans.BX);
  tr->BY = cvt_to_fp(trans.BY);

  tr->Tx = cvt_to_fp(trans.Tx);
  tr->Ty = cvt_to_fp(trans.Ty);
}

/**
 * Basic rotozoom routine. For details see comments in the code.
 */
void rotozoom1(const struct input_params_t* p,
               uint_32* src, uint_32* result, void* is_not_a_serious_warning)
{
  int y;
  int_32 y_a, y_b;
  struct ALTransformFP tr;

  build_fixedpoint_transform(&tr, p);

  // For every pixel (x,y) we perform (u,v) = M * (x,y) + T;
  // this means u =  AX*x + BY*y + Transx
  // and        v =  BX*x + AY*y + Transy
  //
  // Since this is all affine linear, and the coordinates x and y progress 
  // linearly in the loops, we don't have to do the multiplications.
  // Instead we can accumulate the Termx A*x in x_a, B*y in y_b, B*x in x_b
  // and A*y in y_a.
  //
  // We initialise (y_a, y_b) with (Transy, Transy).
  // Then, whenever x is decreased, we add AX to x_a and BX to x_b.
  // Whenever y is decreased, we add AY to y_a and BY to y_b.
  //
  // An invariant vor the y-loop is (ysize-1-y)*AY == y_a - Transy and
  // (ysize-1-y)*BY == y_b - Transx.
  // For the x-loop, the corresponding invariant is (xsize-1-y)*AX == x_a and
  // (xsize-1-y)*BX == x_b.

  y_a = tr.Ty;
  y_b = tr.Tx;
  
  {
  const int xsize_src = p->xsize_src;
  const int ysize_src = p->ysize_src;

  for (y = p->ysize_result-1; y >= 0; --y, y_a += tr.AY, y_b += tr.BY)
    {
      int x;
      int_32 x_a = y_b;
      int_32 x_b = y_a;
      for (x = p->xsize_result-1; x >= 0; --x, x_a += tr.AX, x_b += tr.BX)
	{
	  int u, v;
	  u = x_a >> 16;
	  v = x_b >> 16;
		  
	  if(u >= 0 && u < xsize_src && v >= 0 && v < ysize_src)
	    *result = src[u + v*xsize_src];//(y_<<9)+ (y_<<7)];
		  
	  ++result;
	}
    }
  }
}


/**
 * Basic rotozoom routine with mirror. For details see comments in rotozoom1().
 */
void rotozoom_mirror(const struct input_params_t* p,
                     uint_32* src, uint_32* result,
                     void* is_not_a_serious_warning)
{  
  int y;
  struct ALTransformFP tr;

  int_32 y_a, y_b;

  build_fixedpoint_transform(&tr, p);

  y_a = tr.Ty;
  y_b = tr.Tx;

  {  
  const int xsize_src = p->xsize_src;
  const int ysize_src = p->ysize_src;

  for (y = p->ysize_result-1; y >= 0; --y, y_a += tr.AY, y_b += tr.BY)
    {
      int x;
      int_32 x_a = y_b;
      int_32 x_b = y_a;
      for (x = p->xsize_result-1; x >= 0; --x, x_a += tr.AX, x_b += tr.BX)
	{
	  int u, v;
	  u = abs(x_a >> 16);
	  v = abs(x_b >> 16);
  
          // turned out to be much faster than a % operator
          // (on an athlon-xp 2200+ with gcc-3.3.4)
          while (u >= xsize_src)
            u -= xsize_src;
          while (v >= ysize_src)
            v -= ysize_src;

          *result = src[u + v*xsize_src];//(y_<<9)+ (y_<<7)];

	  ++result;
	}
    }
  }
}

/****************************************************************************/

/**
 * n must be > 0
 */
static void getMinMaxYIndex(struct geo_Point points[], int n,
			    int *i_ymin, int* i_ymax,
			    double* ymin, double* ymax)
{
  int i;
  double ymax_ = points[n-1].y;
  double ymin_ = ymax_;
  int imin = n-1;
  int imax = imin;

  for (i = n-2; i >= 0; --i) {
    double y = points[i].y;

    if (y > ymax_)
      {
	imax = i;
	ymax_ = y;
      }

    if (y < ymin_)
      {
	imin = i;
	ymin_ = y;
      }
      
  }

  *i_ymax = imax;
  *i_ymin = imin;
  *ymin = ymin_;
  *ymax = ymax_;

  //  assert(ymin_ <= ymax_);
  if (!(ymin_ <= ymax_))
    {
      poly_print(points, n);
	  //TODO
      //getchar();
    }
}

/****************************************************************************/

/*
static void transform_print(struct ALTransform* trans)
{
  printf("/ %f\t%f \\\n", trans->AX, trans->BY);
  printf("\\ %f\t%f /\n", trans->BX, trans->AY);
}*/

/*static void transform(struct geo_Point* dst, int x, int y,
		      const struct ALTransform* trans)
{
  dst->x = trans->Tx + trans->A*x + trans->B*y;
  dst->y = trans->Ty - trans->B*x + trans->A*y;
}*/

/****************************************************************************/

static void set_scan_edge(struct EdgeBuffer* edges, 
			  struct geo_Point* p1, struct geo_Point* p2,
			  struct ALTransform* trans, int is_left);


/**
 * Full polygon drawing code here.
 */
void rotozoom2(const struct input_params_t* p,
               uint_32* src, uint_32* result, void* edges_)
{
  uint_32* dst;
	
  double iy1f, iy2f;
  int iy1, iy2;

  struct EdgeBuffer* edges = (struct EdgeBuffer*) edges_;
  struct ALTransform trans, transi;

  struct ScanLine* sline;

  assert(edges->yres == p->ysize_result);

  // now calculate the intersection of the rotozoomed image and the screen
  {
    int i_ymin, i_ymax;
    struct geo_Point points[8];
    int num_points;
    int ok;
    // safety border for the inverse transformation
    const int border = ROTOZOOM_SAFETY_BORDER;

    // calculate the transformation and the inverse transformation
    build_transforms(&trans, &transi, p);

    ok = transform_and_clip(&transi, p->xsize_src, p->ysize_src,
			    p->xsize_result, p->ysize_result,
			    points, &num_points, border);

    if (!ok)
      return; // No intersection -> no drawing

    getMinMaxYIndex(points, num_points, &i_ymin, &i_ymax, &iy1f, &iy2f);
    iy1 = (int) ceil(iy1f);
    iy2 = (int) floor(iy2f);

    {
      int pnt1 = i_ymin;
      int pnt2 = (pnt1 + 1) % num_points;

      do
	{
	  set_scan_edge(edges, points + pnt1, points + pnt2,
			&trans, 1);
	  pnt1 = pnt2;
	  pnt2 = (pnt2 + 1) % num_points;
	} while (pnt1 != i_ymax);

      pnt1 = i_ymax;
      pnt2 = (pnt1 + 1) % num_points;

      do
	{
	  set_scan_edge(edges, points + pnt2, points + pnt1,
			&trans, 0);
	  pnt1 = pnt2;
	  pnt2 = (pnt2 + 1) % num_points;
	} while (pnt1 != i_ymin);
      
    }
  }

  // now walk along the scanlines and do the transform
  sline = edges->scanlines + iy1;
  while (iy1 < iy2)
    {
      int x;
      int_32 AX = cvt_to_fp(trans.AX);
      int_32 BX = cvt_to_fp(trans.BX);

      int_32 x_a = sline->x_a;
      int_32 x_b = sline->x_b;

      int x1 = sline->x1;
      int x2 = sline->x2;

      dst = result + (x1 + iy1* p->xsize_result);
      for (x = x1; x <= x2; ++x)
	{
	  int u, v;

	  u = (x_a >> 16);
	  v = (x_b >> 16);

	  *dst = src[u + v* p->xsize_src];
	  
	  ++dst;
	  x_a += AX;
	  x_b += BX;
	}
      ++iy1;
      ++sline;
    }
}

/****************************************************************************/

static void set_scan_edge(struct EdgeBuffer* edges, 
			  struct geo_Point* p1, struct geo_Point* p2,
			  struct ALTransform* trans, int is_left)
{
  int idy;
  double dx, x1;
  double x_a, x_b, d_a, d_b;
  int y1, y2, x2;
  struct ScanLine* scanline;
  struct ScanLine* end;

  y1 = (int) (p1->y);
  y2 = (int) (p2->y);
  idy = y2 - y1;

  if (idy <= 0)
    return;

  x1 = (int) (p1->x);
  x2 = (int) (p2->x);

  dx = (x2 - x1) / (double) idy;
  d_a = dx*trans->AX + trans->BY;
  d_b = dx*trans->BX + trans->AY;

  x_a = x1*trans->AX + y1*trans->BY + trans->Tx;
  x_b = x1*trans->BX + y1*trans->AY + trans->Ty;

  end = edges->scanlines + y2 + 1;
  for (scanline = edges->scanlines + y1; scanline != end; ++scanline)
    {
      if (is_left)
	{
	  scanline->x1  = (int) x1;
	  scanline->x_a = cvt_to_fp(x_a);
	  scanline->x_b = cvt_to_fp(x_b);
	}
      else
	scanline->x2 = (int)x1;

      x1  += dx;
      x_a += d_a;
      x_b += d_b;
    }
}
