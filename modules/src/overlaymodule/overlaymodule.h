#ifndef INCLUDED_OVERLAYMODULE_H
#define INCLUDED_OVERLAYMODULE_H

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
 NumberType* in_tolerance;
 NumberType* in_alpha_mode;
 FrameBufferType* in_control;
 FrameBufferType* in_1;
 FrameBufferType* in_2;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_tolerance = 0, in_alpha_mode = 1, in_control = 2, in_1 = 3, in_2 = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
