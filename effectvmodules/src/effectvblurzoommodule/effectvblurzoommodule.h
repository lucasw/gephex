#ifndef INCLUDED_EFFECTVBLURZOOMMODULE_H
#define INCLUDED_EFFECTVBLURZOOMMODULE_H

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
 FrameBufferType* in_b;
 NumberType* in_mode;
 NumberType* in_palette;
 NumberType* in_snapinterval;
 NumberType* in_snaptime;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_mode = 1, in_palette = 2, in_snapinterval = 3, in_snaptime = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
