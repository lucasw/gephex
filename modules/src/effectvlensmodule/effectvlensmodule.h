#ifndef INCLUDED_EFFECTVLENSMODULE_H
#define INCLUDED_EFFECTVLENSMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "positiontype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 FrameBufferType* in_b;
 PositionType* in_pos;
 NumberType* in_size;
 NumberType* in_mag;
 NumberType* in_interactive;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_b = 0, in_pos = 1, in_size = 2, in_mag = 3, in_interactive = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
