#ifndef INCLUDED_NOISEMODULE_H
#define INCLUDED_NOISEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_monochrom;
 NumberType* in_outx;
 NumberType* in_outy;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_monochrom = 0, in_outx = 1, in_outy = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
