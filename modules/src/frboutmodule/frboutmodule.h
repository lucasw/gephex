#ifndef INCLUDED_FRBOUTMODULE_H
#define INCLUDED_FRBOUTMODULE_H

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
 FrameBufferType* in_in;
 NumberType* in_options;
 NumberType* in_xsize;
 NumberType* in_ysize;
 NumberType* in_brightness;
 NumberType* in_contrast;
 NumberType* in_gamma;
 NumberType* in_monitor;
 StringType* in_driver;
 StringType* in_server;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_options = 1, in_xsize = 2, in_ysize = 3, in_brightness = 4, in_contrast = 5, in_gamma = 6, in_monitor = 7, in_driver = 8, in_server = 9 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
