#ifndef INCLUDED_X11OUTMODULE_H
#define INCLUDED_X11OUTMODULE_H

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
 FrameBufferType* in_in;
 NumberType* in_xsize;
 NumberType* in_ysize;
 StringType* in_driver;
 StringType* in_server;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_xsize = 1, in_ysize = 2, in_driver = 3, in_server = 4 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
