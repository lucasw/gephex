#ifndef INCLUDED_ENV_TYPE_H
#define INCLUDED_ENV_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

typedef struct EnvType_
{
	double amount;
	double attack;
	double decay;
	double sustain_level;
	double release;
} EnvType;

static __inline void env_initInstance(EnvType* newType)
{
  newType->amount=0.0;
  newType->attack=0.0;
  newType->decay=0.0;
  newType->sustain_level=1.0;
  newType->release=0.0;
}

static __inline EnvType* env_newInstance(void)
{
	EnvType* newType = (EnvType*) malloc(sizeof(EnvType));
	env_initInstance(newType);
	return newType;
}
static __inline void env_assign(EnvType* dst,const EnvType* src)
{
	dst->amount = src->amount;
	dst->attack = src->attack;
	dst->decay = src->decay;
	dst->sustain_level = src->sustain_level;
	dst->release = src->release;
}

static __inline void env_deleteInstance(EnvType* env)
{
	free(env);
}

static __inline int env_serialize(const EnvType* env, char* buffer, int bufferLen)
{
	if (buffer == 0 || bufferLen < 50)
		return 50;
	else
	{
		sprintf(buffer,"%g %g %g %g %g",env->amount, env->attack, env->decay, env->sustain_level, env->release);
		return strlen(buffer)+1;	
	}
}

static __inline void env_deSerialize(const char* buffer,int len, EnvType* env)
{
	if (buffer[0] == 0)
	{
		env_initInstance(env);
	}
	else
	{
	  sscanf(buffer,"%f %f %f %f %f",&env->amount, &env->attack, &env->decay, &env->sustain_level, &env->release);
	}
}

#endif
