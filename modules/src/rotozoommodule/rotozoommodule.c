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

/**
 * Creates the Transformation and its inverse.
 */
static void build_transforms(struct ALTransform* trans,
			     struct ALTransform* transi,
			     double theta, double zoom,
			     int transpx, int transpy,
			     int xsize_src, int ysize_src,
			     int xsize_result, int ysize_result)
{
  double xs, ys;
  double a, b;
  
  if (zoom < 0.00001)
    zoom = 0.00001;

  xs = (xsize_src / (double) xsize_result) * zoom;
  ys = (ysize_src / (double) ysize_result) * zoom;
  a  =  cos(theta);
  trans->AX = xs * a;
  trans->AY = ys * a;
  b = sin(theta);
  trans->BX = xs * b;
  trans->BY = -ys * b;

  trans->Tx = (-(xsize_src/2)-transpx)*trans->AX
    - ((ysize_src/2)+transpy)*trans->BY + (xsize_src/2);
  trans->Ty = (-(xsize_src/2)-transpx)*trans->BX
    - ((ysize_src/2)+transpy)*trans->AY + (ysize_src/2);

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

typedef void (*rotozoomT)(double theta, double zoom, int transpx, int transpy,
			  uint_32* src, int xsize_src, int ysize_src,
			  uint_32* result, int xsize_result, int ysize_result,
			  void*);

static void rotozoom1(double theta, double zoom, int transpx, int transpy,
		      uint_32* src, int xsize_src, int ysize_src,
		      uint_32* result, int xsize_result, int ysize_result,
		      void*);

static void rotozoom2(double theta, double zoom, int transpx, int transpy,
		      uint_32* src, int xsize_src, int ysize_src,
		      uint_32* result, int xsize_result, int ysize_result,
		      void*);


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


void calc_parameters(void* instance, double* theta, double* zoom,
		     int* transpx, int* transpy)
{
  InstancePtr inst = (InstancePtr) instance;  
  //int xsize_out = trim_int(inst->in_outx->number, 0, 1024);
  //int ysize_out = trim_int(inst->in_outy->number, 0, 1024);
  int xsize_out = inst->in_texture->xsize;
  int ysize_out = inst->in_texture->ysize;

  *theta = (M_PI * inst->in_rot->number) / 180;
  *zoom =  trim_double(inst->in_zoom->number,0.001,4);

  *transpx= (int) ((3*xsize_out*trim_double(inst->in_disp->x,0,1))
		   -(xsize_out*1.5));

  *transpy= (int) ((3*ysize_out*trim_double(inst->in_disp->y,0,1))
		    -(ysize_out*1.5));

}

void strongDependencies(Instance* inst, int neededInputs[])
{
  struct geo_Point points[8];
  int num_points;
  int ok;
  struct ALTransform trans, transi;
  // safety border for the inverse transformation
  const int border = ROTOZOOM_SAFETY_BORDER;

  double theta, zoom;
  int transpx, transpy;

  //int xsize_out = trim_int(inst->in_outx->number, 0, 1024);
  //int ysize_out = trim_int(inst->in_outy->number, 0, 1024);
  int xsize_out = inst->in_texture->xsize;
  int ysize_out = inst->in_texture->ysize;

  int xsize_text = inst->in_texture->xsize;
  int ysize_text = inst->in_texture->ysize;

  MyInstancePtr my = inst->my;

  calc_parameters(inst, &theta, &zoom, &transpx, &transpy);

  // calculate the transformation and the inverse transformation
  build_transforms(&trans, &transi, theta, zoom,
		   transpx, transpy, xsize_text, ysize_text,
		   xsize_out, ysize_out);

  ok = transform_and_clip(&transi, xsize_text, ysize_text,
			  xsize_out, ysize_out,
			  points, &num_points, border);

  my->back_needed = 1;
  my->text_needed = 1;
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

void patchLayout(Instance* inst, int out2in[])
{
  if (!inst->in_copy_background->number)
    out2in[out_r] = in_background;
}

/****************************************************************************/

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  double theta, zoom;
  int transpx, transpy;

  //int xsize_out = trim_int(inst->in_outx->number, 0, 1024);
  //int ysize_out = trim_int(inst->in_outy->number, 0, 1024);
  int xsize_out = inst->in_texture->xsize;
  int ysize_out = inst->in_texture->ysize;

  int xsize_text = inst->in_texture->xsize;
  int ysize_text = inst->in_texture->ysize;

  calc_parameters(instance, &theta, &zoom, &transpx, &transpy);

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

  if (my->usesEdgeBuffer && my->edges.yres != ysize_out)
    {
      if (my->edges.scanlines != 0)
	free(my->edges.scanlines);

      my->edges.scanlines = (struct ScanLine*) malloc(sizeof(*(my->edges.scanlines))*ysize_out);
      my->edges.yres = ysize_out;
    }

  if (inst->in_copy_background->number && my->back_needed)
    {
      framebuffer_assign(inst->out_r, inst->in_background);
    }

  {
    FrameBufferAttributes attribs;
    attribs.xsize = xsize_out;
    attribs.ysize = ysize_out;
    framebuffer_changeAttributes(inst->out_r,&attribs);
  }

  if (my->text_needed)
    {
      my->rotozoom(theta, zoom, transpx, transpy,
		   inst->in_texture->framebuffer, xsize_text, ysize_text,
		   inst->out_r->framebuffer, xsize_out, ysize_out,
		   &my->edges);
    }
}

/****************************************************************************/

/**
 * Basic rotozoom routine. For details see comments in the code.
 */
void rotozoom1(double theta, double zoom, int transpx, int transpy,
	       uint_32* src, int xsize_src, int ysize_src,
	       uint_32* result, int xsize_result, int ysize_result,
	       void* is_not_a_serious_warning)
{
  double a_x = zoom * cos(theta);
  double a_y = a_x;
  double b_x = zoom * sin(theta);
  double b_y = -b_x;
  double xs, ys;
  
  int y;
  int Transx, Transy;  
  int y_a, y_b, AX, AY, BX, BY;

  // generate Transfom
  //
  // ( AX  BY )   ( x )    ( Transx )   ( u )
  // (        ) * (   ) +  (        ) = (
  // ( BX  AY )   ( y )    ( Transy )   ( v )
  //
  // \-------/            \--------/
  //     M                    T

  xs = (xsize_src / (double) xsize_result);
  ys = (ysize_src / (double) ysize_result);
  a_x *= xs;
  a_y *= ys;
  b_x *= xs;
  b_y *= ys;
  
  AX = (int_32) (FIXEDPNT_SCALE*a_x);
  AY = (int_32) (FIXEDPNT_SCALE*a_y);
  BX = (int_32) (FIXEDPNT_SCALE*b_x);
  BY = (int_32) (FIXEDPNT_SCALE*b_y);

  Transx = (-(xsize_src/2)-transpx)*AX - ((ysize_src/2)+transpy)*BY
    + ((xsize_src/2)<<16);
  Transy =  (-(xsize_src/2)-transpx)*BX - ((ysize_src/2)+transpy)*AY
    + ((ysize_src/2)<<16);

  // For every pixel (x,y) we perform (u,v) = (x,y) * M + T;
  // this means u =  AX*x + BY*y + Transx
  // and        v =  BX*x + AY*y + Transy
  //
  // Since this is all linear, and the coordinates x and y progress linearly
  // in out loop, we don't have to do the multiplications.
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

  y_a = Transy;
  y_b = Transx;
  
  for (y = ysize_result-1; y >= 0; --y, y_a += AY, y_b += BY)
    {
      int x;
      int x_a = 0;
      int x_b = 0;
      for (x = xsize_result-1; x >= 0; --x, x_a += AX, x_b += BX)
	{
	  int u, v;
	  u = ((x_a + y_b) >> 16);
	  v = ((y_a + x_b) >> 16);
		  
	  if(u >= 0 && u < xsize_src && v >= 0 && v < ysize_src)
	    *result = src[u + v*xsize_src];//(y_<<9)+ (y_<<7)];
		  
	  ++result;
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
void rotozoom2(double theta, double zoom, int transpx, int transpy,
	       uint_32* src, int xsize_src, int ysize_src,
	       uint_32* result, int xsize_result, int ysize_result,
	       void* edges_)
{
  uint_32* dst;
	
  double iy1f, iy2f;
  int iy1, iy2;

  struct EdgeBuffer* edges = (struct EdgeBuffer*) edges_;
  struct ALTransform trans, transi;

  struct ScanLine* sline;

  assert(edges->yres == ysize_result);

  // now calculate the intersection of the rotozoomed image and the screen
  {
    int i_ymin, i_ymax;
    struct geo_Point points[8];
    int num_points;
    int ok;
    // safety border for the inverse transformation
    const int border = ROTOZOOM_SAFETY_BORDER;

    // calculate the transformation and the inverse transformation
    build_transforms(&trans, &transi, theta, zoom,
		    transpx, transpy, xsize_src, ysize_src,
		    xsize_result, ysize_result);

    ok = transform_and_clip(&transi, xsize_src, ysize_src,
			    xsize_result, ysize_result,
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
      int_32 AX = (int_32) (trans.AX*FIXEDPNT_SCALE);
      int_32 BX = (int_32) (trans.BX*FIXEDPNT_SCALE);

      int_32 x_a = sline->x_a;
      int_32 x_b = sline->x_b;

      int x1 = sline->x1;
      int x2 = sline->x2;

      dst = result + (x1 + iy1*xsize_result);
      for (x = x1; x <= x2; ++x)
	{
	  int u, v;

	  u = (x_a >> 16);
	  v = (x_b >> 16);

	  *dst = src[u + v*xsize_src];
	  
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
	  scanline->x_a = (int_32) (x_a * FIXEDPNT_SCALE);
	  scanline->x_b = (int_32) (x_b * FIXEDPNT_SCALE);
	}
      else
	scanline->x2 = (int)x1;

      x1  += dx;
      x_a += d_a;
      x_b += d_b;
    }
}
