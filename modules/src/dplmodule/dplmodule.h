#ifndef INCLUDED_DPLMODULE_H
#define INCLUDED_DPLMODULE_H

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
 NumberType* in_angle;
 FrameBufferType* in_displ_mask;
 FrameBufferType* in_in;
 StringType* in_mode;
 FrameBufferType* out_out;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_angle = 1, in_displ_mask = 2, in_in = 3, in_mode = 4 };
enum Outputs { out_out = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
