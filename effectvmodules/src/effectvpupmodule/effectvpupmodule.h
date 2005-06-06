#ifndef INCLUDED_EFFECTVPUPMODULE_H
#define INCLUDED_EFFECTVPUPMODULE_H

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
 FrameBufferType* in_b;
 StringType* in_mode;
 NumberType* in_paraminc;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_mode = 1, in_paraminc = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
