#ifndef INCLUDED_NUMENVMODULE_H
#define INCLUDED_NUMENVMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "envtype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_amount;
 NumberType* in_attack;
 NumberType* in_decay;
 NumberType* in_sustain_level;
 NumberType* in_release;
 EnvType* out_result;
} Instance, *InstancePtr;
enum Inputs { in_amount = 0, in_attack = 1, in_decay = 2, in_sustain_level = 3, in_release = 4 };
enum Outputs { out_result = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
