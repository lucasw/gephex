#ifndef INCLUDED_IMGMULMODULE_H
#define INCLUDED_IMGMULMODULE_H

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
 NumberType* in_amount;
 FrameBufferType* in_input1;
 FrameBufferType* in_input2;
 FrameBufferType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_input1 = 1, in_input2 = 2 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
