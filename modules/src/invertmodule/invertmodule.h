#ifndef INCLUDED_INVERTMODULE_H
#define INCLUDED_INVERTMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "framebuffertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 FrameBufferType* in_b;
 StringType* in_routine;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_routine = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
