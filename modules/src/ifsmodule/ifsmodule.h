#ifndef INCLUDED_IFSMODULE_H
#define INCLUDED_IFSMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "ifstype.h"
#include "framebuffertype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_x_size;
 NumberType* in_y_size;
 NumberType* in_num_dot;
 IfsType* in_ifs;
 FrameBufferType* out_out;
} Instance, *InstancePtr;
enum Inputs { in_x_size = 0, in_y_size = 1, in_num_dot = 2, in_ifs = 3 };
enum Outputs { out_out = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
