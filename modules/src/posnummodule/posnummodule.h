#ifndef INCLUDED_POSNUMMODULE_H
#define INCLUDED_POSNUMMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "positiontype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 PositionType* in_pos;
 NumberType* out_xresult;
 NumberType* out_yresult;
} Instance, *InstancePtr;
enum Inputs { in_pos = 0 };
enum Outputs { out_xresult = 0, out_yresult = 1 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
