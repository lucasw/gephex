#ifndef INCLUDED_STATICCOLORMODULE_H
#define INCLUDED_STATICCOLORMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "framebuffertype.h"
#include "rgbtype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 RGBType* in_col;
 NumberType* in_xsize;
 NumberType* in_ysize;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_col = 0, in_xsize = 1, in_ysize = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
