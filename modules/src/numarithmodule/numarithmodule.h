#ifndef INCLUDED_NUMARITHMODULE_H
#define INCLUDED_NUMARITHMODULE_H

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
 NumberType* in_lhs;
 NumberType* in_rhs;
 StringType* in_op;
 NumberType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_lhs = 0, in_rhs = 1, in_op = 2 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
