#ifndef INCLUDED_NUMPOSMODULE_H
#define INCLUDED_NUMPOSMODULE_H

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
 NumberType* in_xpos;
 NumberType* in_ypos;
 PositionType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_xpos = 0, in_ypos = 1 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
