#ifndef INCLUDED_NUMLFOMODULE_H
#define INCLUDED_NUMLFOMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "lfotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_amount;
 NumberType* in_frequ;
 LfoType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_frequ = 1 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
