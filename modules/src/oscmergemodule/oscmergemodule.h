#ifndef INCLUDED_OSCMERGEMODULE_H
#define INCLUDED_OSCMERGEMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "osctype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 OscType* in_1;
 OscType* in_2;
 OscType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_1 = 0, in_2 = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
