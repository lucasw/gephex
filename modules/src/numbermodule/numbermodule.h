#ifndef INCLUDED_NUMBERMODULE_H
#define INCLUDED_NUMBERMODULE_H

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
 NumberType* in_tpf;
 NumberType* in_min;
 NumberType* in_max;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_tpf = 0, in_min = 1, in_max = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
