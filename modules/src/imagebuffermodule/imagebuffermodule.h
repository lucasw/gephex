#ifndef INCLUDED_IMAGEBUFFERMODULE_H
#define INCLUDED_IMAGEBUFFERMODULE_H

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
 NumberType* in_bsize;
 NumberType* in_bpos;
 NumberType* in_record;
 FrameBufferType* in_b;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_bsize = 0, in_bpos = 1, in_record = 2, in_b = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
