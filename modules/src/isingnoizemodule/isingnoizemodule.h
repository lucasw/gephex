#ifndef INCLUDED_ISINGNOIZEMODULE_H
#define INCLUDED_ISINGNOIZEMODULE_H

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
 NumberType* in_temp;
 NumberType* in_border_growth;
 NumberType* in_spont_growth;
 NumberType* in_outx;
 NumberType* in_outy;
 FrameBufferType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_temp = 0, in_border_growth = 1, in_spont_growth = 2, in_outx = 3, in_outy = 4 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
