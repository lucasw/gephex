#include "ifsmodule.h"

#include <algorithm>
#include <cstdlib>
#include <cassert>

#include "minmax.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

using std::min;
using std::max;


static logT s_log;

typedef struct _MyInstance {

  uint_32* frameBuffer;
  int xSize;
  int ySize;
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
  MyInstance* my = new MyInstance;

  my->frameBuffer= 0;
  my->xSize=0;
  my->ySize=0;

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  delete[] my->frameBuffer;
  delete my;
}

struct Val2Pal
{
  Val2Pal(uint_32* pal_):pal(pal_){};
  uint_32* pal;
  uint_32 operator()(uint_32 val)
  {
    unsigned int index;
    if (val > 255)
      index=255;
    else
      index=val;
    return pal[index];
  };
};


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int numDots = trim_int(inst->in_num_dot->number,1,10000000);
  int recursionDeep = trim_int(inst->in_num_rec->number,0,40);
  int amount = (int) (trim_double(inst->in_amount->number,0,1) * 255);

  uint_32 pal[256];
  for (int i=0;i!=256;++i)
    {
      uint_32 r,g,b;
      r=min(255,i);
      g=min(255,i);
      b=min(255,i);
      pal[i]=r|(g<<8)|(b<<16);
    }

  // add size change code
  FrameBufferAttributes attrib;
  attrib.xsize=trim_int(inst->in_x_size->number,0,FRAMEBUFFER_X_MAX);
  attrib.ysize=trim_int(inst->in_y_size->number,0,FRAMEBUFFER_Y_MAX);
  if (attrib.xsize==0||attrib.ysize==0)
    {
      attrib.xsize=640;
      attrib.ysize=480;
    }
  framebuffer_changeAttributes(inst->out_out,&attrib);

  if (my->frameBuffer==0||inst->out_out->xsize!=my->xSize||inst->out_out->ysize!=my->ySize)
    {
      s_log(2,"change");
      delete[] my->frameBuffer;
      my->xSize=inst->out_out->xsize;
      my->ySize=inst->out_out->ysize;
      my->frameBuffer= new uint_32[my->xSize*my->ySize];

    }



  // clear background
  std::fill(my->frameBuffer,
	    &(my->frameBuffer[my->xSize*my->ySize]),
	    0);

  for (int i=0;i!=numDots;++i)
    {
      double x = 0.0;
      double y = 0.0;

      for (int j=0;j!=recursionDeep;++j)
	{
	  // random chose in [0..numFuns-1]
	  int fun=static_cast<int>((static_cast<double>(rand())/RAND_MAX)*inst->in_ifs->numfun);
	  double xn=inst->in_ifs->ifs[0][fun]*x+inst->in_ifs->ifs[1][fun]*y+inst->in_ifs->ifs[4][fun];
	  double yn=inst->in_ifs->ifs[2][fun]*x+inst->in_ifs->ifs[3][fun]*y+inst->in_ifs->ifs[5][fun];
	  x=xn;y=yn;
	}

      // hm there needs to be some aspect correction
      int x_pos=(int)((x+1.0)*my->xSize/2);
      int y_pos=(int)((y+1.0)*my->ySize/2);
      
      // clipping
      if((x_pos>0)&&(x_pos<my->xSize)&&(y_pos>0)&&(y_pos<my->ySize))
      {
	// increase lightness
	my->frameBuffer[x_pos+y_pos*my->xSize]+=amount;
      }
    }
  
  // copy in the output frame
  // and replace intensities with palette entry
  std::transform(my->frameBuffer,
		 &(my->frameBuffer[my->xSize*my->ySize]),
		 inst->out_out->framebuffer,Val2Pal(pal));
}

