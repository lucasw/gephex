#ifndef INCLUDED_EFFECTVSIMURAMODULE_H
#define INCLUDED_EFFECTVSIMURAMODULE_H

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
 FrameBufferType* in_b;
 NumberType* in_color;
 NumberType* in_mirror;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_color = 1, in_mirror = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
