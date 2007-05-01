#ifndef INCLUDED_MIRRORMODULE_H
#define INCLUDED_MIRRORMODULE_H

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
 NumberType* in_lrrl;
 NumberType* in_tbbt;
 NumberType* in_mode;
 FrameBufferType* in_1;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_lrrl = 0, in_tbbt = 1, in_mode = 2, in_1 = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
