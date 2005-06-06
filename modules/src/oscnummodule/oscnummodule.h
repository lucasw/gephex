#ifndef INCLUDED_OSCNUMMODULE_H
#define INCLUDED_OSCNUMMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "osctype.h"
#include "stringtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 OscType* in_osc;
 StringType* in_address;
 NumberType* out_num;
} Instance, *InstancePtr;
enum Inputs { in_osc = 0, in_address = 1 };
enum Outputs { out_num = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
