#ifndef INCLUDED_BLURMODULE_H
#define INCLUDED_BLURMODULE_H

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
 NumberType* in_x;
 FrameBufferType* in_b;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_x = 0, in_b = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
