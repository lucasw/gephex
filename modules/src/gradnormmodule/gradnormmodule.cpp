#include "gradnormmodule.h"

#if _MSC_VER > 1200
#include <stdint.h>
#else
#include "basic_types.h"
typedef uint_32 uint32_t;
typedef uint_8  uint8_t;
#endif

#include <algorithm>
#include <cmath>

static logT s_log;

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

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

inline double grey(uint32_t& rgb)
{
  return ((rgb>>8)&0xFF);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // Add your effect here!
  FrameBufferAttributes attribs;
  framebuffer_getAttributes(inst->in_b, &attribs);
  framebuffer_changeAttributes(inst->out_r, &attribs);

  int xsize      = inst->in_b->xsize;
  int ysize      = inst->in_b->ysize;
  int index      = 1 + xsize;
  uint_32* fb    = inst->in_b->framebuffer;
  uint_32* outfb = inst->out_r->framebuffer;

  if (xsize > 3 && ysize > 3)
    {
      for (int y = ysize-3; y >= 0; --y, index += 2)
        for (int x = xsize-3; x >= 0; --x, ++index)
          {
            double a1=grey(fb[index - 1 - xsize]);
            double a2=grey(fb[index     - xsize]);
            double a3=grey(fb[index + 1 - xsize]);
            double a4=grey(fb[index - 1        ]);
            double a6=grey(fb[index + 1        ]);
            double a7=grey(fb[index - 1 + xsize]);
            double a8=grey(fb[index     + xsize]);
            double a9=grey(fb[index + 1 + xsize]);

            // derivate in the two direktions with the sobel operator
            double gradx=(-a1+a3-2*a4+2*a6-a7+a9)/8.0;
            double grady=(-a1-2*a2-a3+a7+2*a8+a9)/8.0;

            // norm
            double gn = sqrt(gradx*gradx+grady*grady);
            //            uint8_t gv;
	
            uint8_t* out=reinterpret_cast<uint8_t*>(outfb + index);
	
			uint8_t v = static_cast<int>(gn*10);
			if (v > 255)
				v = 255;

            *out = *(out+1) = *(out+2) = *(out+3) = v;            
      }
    }
}

