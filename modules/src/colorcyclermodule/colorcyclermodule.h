#ifndef INCLUDED_COLORCYCLERMODULE_H
#define INCLUDED_COLORCYCLERMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "rgbtype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_mode;
 RGBType* out_Farbe;
} Instance, *InstancePtr;
enum Inputs { in_mode = 0 };
enum Outputs { out_Farbe = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
