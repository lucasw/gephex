#ifndef INCLUDED_XFADEMODULE_H
#define INCLUDED_XFADEMODULE_H

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
 NumberType* in_x;
 FrameBufferType* in_1;
 FrameBufferType* in_2;
 StringType* in_routine;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_x = 0, in_1 = 1, in_2 = 2, in_routine = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
void patchLayout(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
