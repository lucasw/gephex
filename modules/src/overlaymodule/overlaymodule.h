#ifndef INCLUDED_OVERLAYMODULE_H
#define INCLUDED_OVERLAYMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "framebuffertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_tolerance;
 FrameBufferType* in_control;
 FrameBufferType* in_1;
 FrameBufferType* in_2;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_tolerance = 0, in_control = 1, in_1 = 2, in_2 = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
