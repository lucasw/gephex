#ifndef INCLUDED_RESULTMODULE_H
#define INCLUDED_RESULTMODULE_H

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
 NumberType* in_shut_up;
} Instance, *InstancePtr;
enum Inputs { in_in = 0, in_shut_up = 1 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
