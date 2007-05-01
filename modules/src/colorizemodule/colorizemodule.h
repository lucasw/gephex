#ifndef INCLUDED_COLORIZEMODULE_H
#define INCLUDED_COLORIZEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "rgbtype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 RGBType* in_color;
 NumberType* in_mode;
 NumberType* in_tolerance;
 FrameBufferType* in_1;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_color = 0, in_mode = 1, in_tolerance = 2, in_1 = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
