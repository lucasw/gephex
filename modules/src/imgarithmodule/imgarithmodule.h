#ifndef INCLUDED_IMGARITHMODULE_H
#define INCLUDED_IMGARITHMODULE_H

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
 NumberType* in_amount;
 FrameBufferType* in_input1;
 FrameBufferType* in_input2;
 StringType* in_mmx;
 StringType* in_op;
 FrameBufferType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_input1 = 1, in_input2 = 2, in_mmx = 3, in_op = 4 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
void strongDependencies(Instance*,int[]);
#ifdef __cplusplus
}
#endif

#endif
