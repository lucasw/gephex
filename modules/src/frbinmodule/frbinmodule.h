#ifndef INCLUDED_FRBINMODULE_H
#define INCLUDED_FRBINMODULE_H

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
 StringType* in_fileName;
 NumberType* in_flush;
 NumberType* in_frame;
 NumberType* in_x_size;
 NumberType* in_y_size;
 StringType* in_cache;
 FrameBufferType* out_result;
 NumberType* out_position;
 NumberType* out_length;
} Instance, *InstancePtr;
enum Inputs { in_fileName = 0, in_flush = 1, in_frame = 2, in_x_size = 3, in_y_size = 4, in_cache = 5 };
enum Outputs { out_result = 0, out_position = 1, out_length = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
