#ifndef INCLUDED_JUMPMODULE_H
#define INCLUDED_JUMPMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_in;
 NumberType* in_thr;
 NumberType* in_upper;
 NumberType* in_lower;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_thr = 1, in_upper = 2, in_lower = 3 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
