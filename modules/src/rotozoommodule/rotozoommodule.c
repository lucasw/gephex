#include "rotozoommodule.h"

#include <string.h>
#include <math.h>
#include <limits.h>


#undef M_PI
const double M_PI = 3.1415;

typedef struct _MyInstance {

  int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
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


int A;
int B;

float fx(float x, float y)
{
  return (x*A) + (y*B);
}

float fy(float x,float y)
{
  return (y*A) - (x*B);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int x_a, y_a, x_b, y_b;
	
  double a1 = (2*M_PI * (double) inst->in_rot->number) / (double)(UINT_MAX);
  double b1 = (4. * (double) inst->in_zoom->number)  / (double)(UINT_MAX);
  double alpha = a1;
  double beta = b1;
	
  double a_ = beta * cos(alpha);
  double b_ = -beta * sin(alpha);

  int xsize = inst->in_b->xsize;

  int ysize = inst->in_b->ysize;
  int maxPixelOffset = xsize*ysize;
  unsigned int* src = inst->in_b->framebuffer;
  unsigned int* result;
  int y;
  int ATrans, BTrans;
  int transpx= (int) (((3*xsize*(double)inst->in_disp->x)/(double)UINT_MAX)-(xsize*1.5));
  int transpy= (int) (((3*ysize*(double)inst->in_disp->y)/(double)UINT_MAX)-(ysize*1.5));

  FrameBufferAttributes attribs;

  attribs.xsize = xsize;
  attribs.ysize = ysize;
  framebuffer_changeAttributes(inst->out_r,&attribs);

  result = inst->out_r->framebuffer;

  A = (int) (65536*a_);
  B = (int) (65536*b_);
  ATrans = (-(xsize/2)-transpx)*A;
  BTrans = (-(xsize/2)-transpx)*B;
  //A = a_;
  //B = b_;
	
  y_a = (-(ysize/2)-transpy)*A + ((ysize/2)<<16);
  y_b = (-(ysize/2)-transpy)*B + ((xsize/2)<<16);
  
  for (y = ysize-1; y >= 0; --y)
  {
      int x;
      x_a = ATrans;
      x_b = BTrans;
      for (x = xsize-1; x >= 0; --x)
	  {
		  int x_, y_;
		  x_ = ((x_a + y_b) >> 16);// +320;
		  y_ = ((y_a - x_b) >> 16);// + 240;
		  
		  if(x_>=0&&x_<xsize&&y_>=0&&y_<ysize)
			  *result = src[x_ + y_*xsize];//(y_<<9)+ (y_<<7)];
		  else
			  *result = 0; //TODO  
		  
		  ++result;
		  x_a += A;
		  x_b += B;
	  }
      y_a += A;
      y_b += B;
  }

}

