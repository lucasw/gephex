#ifndef __INCLUDED_NUMBER_TYPE_H__
#define __INCLUDED_NUMBER_TYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic_types.h"

// Zahl von 0 bis (2^32)-1
typedef struct NumberType_
{
	uint_32 number;
} NumberType;

static __inline void number_initInstance(NumberType* newType)
{
	newType->number = 0;
}

static __inline NumberType* number_newInstance(void)
{
	NumberType* newType = (NumberType*) malloc(sizeof(NumberType));
	number_initInstance(newType);
	return newType;
}
static __inline void number_assign(NumberType* dst,const NumberType* src)
{
	dst->number = src->number;
}

static __inline void number_deleteInstance(NumberType* num)
{
	free(num);
}

static __inline int number_serialize(NumberType* number, char* buffer, int bufferLen)
{
	if (bufferLen<14||buffer==0)
	{
		return 14;
	}
	else
	{
		sprintf(buffer,"%u",number->number);
		return strlen(buffer)+1;
	}
}

static __inline void number_deSerialize(const char* buffer,int len, NumberType* number)
{
	if (buffer[0] == 0)
	{
		number_initInstance(number);
	}
	else
	{
		sscanf(buffer,"%u",&number->number);
	}
}

#endif
