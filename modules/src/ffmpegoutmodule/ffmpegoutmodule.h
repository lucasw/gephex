#ifndef INCLUDED_FFMPEGOUTMODULE_H
#define INCLUDED_FFMPEGOUTMODULE_H

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
 StringType* in_encoding;
 NumberType* in_xsize;
 NumberType* in_ysize;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_filename = 1, in_encoding = 2, in_xsize = 3, in_ysize = 4 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
