#ifndef INCLUDED_EFFECTVFIREMODULE_H
#define INCLUDED_EFFECTVFIREMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 FrameBufferType* in_b;
 NumberType* in_bg;
 StringType* in_mode;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_bg = 1, in_mode = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
