#ifndef INCLUDED_TIMESOURCEMODULE_H
#define INCLUDED_TIMESOURCEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "stringtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 StringType* in_mode;
 NumberType* out_Time;
} Instance, *InstancePtr;
enum Inputs { in_mode = 0 };
enum Outputs { out_Time = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
