#ifndef INCLUDED_NUMBER2COLORMODULE_H
#define INCLUDED_NUMBER2COLORMODULE_H

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
 NumberType* in_r;
 NumberType* in_g;
 NumberType* in_b;
 RGBType* out_color;
} Instance, *InstancePtr;
enum Inputs { in_r = 0, in_g = 1, in_b = 2 };
enum Outputs { out_color = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
