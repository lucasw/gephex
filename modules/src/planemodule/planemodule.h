#ifndef INCLUDED_PLANEMODULE_H
#define INCLUDED_PLANEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "framebuffertype.h"
#include "positiontype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_t;
 NumberType* in_rot;
 PositionType* in_pos;
 FrameBufferType* in_b;
 NumberType* in_xres;
 NumberType* in_yres;
 NumberType* in_d;
 NumberType* in_shading;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_t = 0, in_rot = 1, in_pos = 2, in_b = 3, in_xres = 4, in_yres = 5, in_d = 6, in_shading = 7 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
