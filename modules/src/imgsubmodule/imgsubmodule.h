#ifndef INCLUDED_IMGSUBMODULE_H
#define INCLUDED_IMGSUBMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"
#include "framebuffertype.h"
#include "stringtype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_amount;
 FrameBufferType* in_input1;
 FrameBufferType* in_input2;
 StringType* in_routine;
 FrameBufferType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_input1 = 1, in_input2 = 2, in_routine = 3 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
