extern "C" 
{
	#include "dllmodule.h"
	#include "framebuffertype.h"
}

#include <stdlib.h>
#include <string.h>

#include "combine.xpm"

static const char* SPEC = 
"mod_spec { name=mod_combineModule; number_of_inputs=3; number_of_outputs=1; "
"deterministic=true; }";
static const char* INPUT_SPECS[] = 
{ 
	"input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }",
	"input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }",
	"input_spec { type=typ_framebuffer; const=true; strong_dependency=true; }"
};
static const char* OUTPUT_SPECS[] = 
{ 
	"output_spec { type=typ_framebuffer; }", 
};

typedef struct instance_
{
  FrameBufferType result;
  FrameBufferType* input_r;
  FrameBufferType* input_g;
  FrameBufferType* input_b;
} Instance, *InstancePtr;

int init(logT)
{
  return 1;
}

void*  newInstance(void)
{
  InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));

  inst->result.xsize = 640; inst->result.ysize = 480;
  inst->result.framebuffer = (int*) malloc(sizeof(int) * 640*480);

  return inst;
}

void deleteInstance(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  free(inst->result.framebuffer);
  free(inst);
}

int setInput(void* instance,int index,void* typePointer)
{	
  InstancePtr inst = (InstancePtr) instance;	

	switch(index)
	{
		case 0:
		  inst->input_r = (FrameBufferType*) typePointer;
			break;
		case 1:
		  inst->input_g = (FrameBufferType*) typePointer;
			break;
		case 2:
		  inst->input_b = (FrameBufferType*) typePointer;
			break;
	}

  return 0;
}

void * getOutput (void* instance,int index)
{
  InstancePtr inst = (InstancePtr) instance;
  return &(inst->result);
}

// ---------------------------------------------------------------------------
// Main Part
// ---------------------------------------------------------------------------

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;

  int xsize, ysize; 
	int *srcr, *srcg, *srcb, *dst;

  srcr = (int*)inst->input_r->framebuffer;
  srcg = (int*)inst->input_g->framebuffer;
  srcb = (int*)inst->input_b->framebuffer;
  xsize = 640;
  ysize = 480;

  dst = inst->result.framebuffer;

	int xysize = xsize * ysize;

	for(int i=xysize; i--;)
	{
		char* tmpr = (char*)srcr;
		char* tmpg = (char*)srcg;
		char* tmpb = (char*)srcb;

		*dst = (tmpr[2] << 16) | (tmpg[1] << 8) | tmpb[0];

		dst++; 
		srcr++;
		srcg++;
		srcb++;
	}
}

const char* getInputSpec (int index)
{
  return INPUT_SPECS[index];
}
	
const char* getOutputSpec (int index)
{
  return OUTPUT_SPECS[index];
}

const char* getSpec(void)
{
  return SPEC;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=RGBCombine group=Mixer inputs=[3 Bild Bild Bild] outputs=[1 Bild] type=xpm}";
  char* tmpBuf;
  int reqLen = strlen(INFO) + 1 + getSizeOfXPM(combine_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(combine_xpm);
      tmpBuf = (char*) malloc(reqLen);
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO)+1;
      for (i = 0; i < lines; ++i)
	  {
		  char* source = combine_xpm[i];
		  memcpy(offset,source,strlen(source)+1);
		  offset += strlen(source) + 1;
	  }			
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
  }
  return reqLen;
}
