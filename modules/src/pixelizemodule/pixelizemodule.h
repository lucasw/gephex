#ifndef INCLUDED_PIXELIZEMODULE_H
#define INCLUDED_PIXELIZEMODULE_H

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
 NumberType* in_bsize;
 FrameBufferType* in_src;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_bsize = 0, in_src = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void patchLayout(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
