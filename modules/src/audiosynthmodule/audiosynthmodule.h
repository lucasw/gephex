#ifndef INCLUDED_AUDIOSYNTHMODULE_H
#define INCLUDED_AUDIOSYNTHMODULE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "dllmodule.h"
#include "envtype.h"
#include "stringtype.h"
#include "lfotype.h"
#include "audiotype.h"
#include "numbertype.h"

struct _MyInstance;
typedef struct _Instance
{
struct _MyInstance* my;
 NumberType* in_key_press;
 NumberType* in_key;
 NumberType* in_amplitude;
 StringType* in_signal;
 EnvType* in_a_env;
 LfoType* in_a_lfo;
 EnvType* in_f_env;
 LfoType* in_f_lfo;
 NumberType* in_sample_rate;
 AudioType* out_r;
} Instance, *InstancePtr;
enum Inputs { in_key_press = 0, in_key = 1, in_amplitude = 2, in_signal = 3, in_a_env = 4, in_a_lfo = 5, in_f_env = 6, in_f_lfo = 7, in_sample_rate = 8 };
enum Outputs { out_r = 0 };

struct _MyInstance* construct(void);
void destruct(struct _MyInstance*);
int init(logT log_function);
#ifdef __cplusplus
}
#endif

#endif
