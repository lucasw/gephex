#ifndef INCLUDED_EFFECTVEDGEMODULE_H
#define INCLUDED_EFFECTVEDGEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "framebuffertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 FrameBufferType* in_b;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
