#ifndef INCLUDED_SDLOUTPUTMODULE_H
#define INCLUDED_SDLOUTPUTMODULE_H

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
 FrameBufferType* in_in;
 NumberType* in_xsize;
 NumberType* in_ysize;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_xsize = 1, in_ysize = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
