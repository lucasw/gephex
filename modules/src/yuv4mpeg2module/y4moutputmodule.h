#ifndef INCLUDED_Y4MOUTPUTMODULE_H
#define INCLUDED_Y4MOUTPUTMODULE_H

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
 StringType* in_filename;
 NumberType* in_xsize;
 NumberType* in_ysize;
 StringType* in_color_model;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_filename = 1, in_xsize = 2, in_ysize = 3, in_color_model = 4 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
