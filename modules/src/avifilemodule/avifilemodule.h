#ifndef INCLUDED_AVIFILEMODULE_H
#define INCLUDED_AVIFILEMODULE_H

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
 StringType* in_fileName;
 NumberType* in_seek;
 NumberType* in_position;
 FrameBufferType* out_result;
 NumberType* out_position;
} Instance, *InstancePtr;
enum Inputs { in_fileName = 0, in_seek = 1, in_position = 2 };
enum Outputs { out_result = 0, out_position = 1 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
