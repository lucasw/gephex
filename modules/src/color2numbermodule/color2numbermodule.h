#ifndef INCLUDED_COLOR2NUMBERMODULE_H
#define INCLUDED_COLOR2NUMBERMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "rgbtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 RGBType* in_color;
 NumberType* out_r;
 NumberType* out_g;
 NumberType* out_b;
} Instance, *InstancePtr;
enum Inputs { in_color = 0 };
enum Outputs { out_r = 0, out_g = 1, out_b = 2 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
