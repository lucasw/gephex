#ifndef INCLUDED_SUBMODULE_H
#define INCLUDED_SUBMODULE_H

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
 NumberType* in_lhs;
 NumberType* in_rhs;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_lhs = 0, in_rhs = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
