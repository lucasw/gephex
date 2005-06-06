#ifndef INCLUDED_NUMOSCMODULE_H
#define INCLUDED_NUMOSCMODULE_H

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
 NumberType* in_value;
 StringType* in_address;
 OscType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_value = 0, in_address = 1 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
