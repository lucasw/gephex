#include <stdlib.h>
#include <string.h>

// Zahl von 0 bis (2^32)-1
typedef struct StringType_
{
	char* text;
} StringType;

static __inline void string_charAssign(StringType* dst,const char* src)
{
	int lens = strlen(src)+1;
	if (dst->text != 0)
		free(dst->text);

	dst->text = (char*) malloc(lens);
	memcpy(dst->text,src,lens);
}


static __inline void string_initInstance(StringType* newString)
{
	newString->text = 0;
	string_charAssign(newString,"null");	
}

static __inline StringType* string_newInstance(void)
{
	StringType* newType = (StringType*) malloc(sizeof(StringType));	

	string_initInstance(newType);
	return newType;
}

static __inline void string_assign(StringType* dst,const StringType* src)
{
	string_charAssign(dst,src->text);
}

static __inline void string_destroyInstance(StringType* num)
{
   free(num->text);
}

static __inline void string_deleteInstance(StringType* num)
{
	string_destroyInstance(num);
	free(num);
}

static __inline int string_serialize(const StringType* string, char* buffer,
				     int bufferLen)
{
	int reqLen = strlen(string->text) + 1;

	if (bufferLen >= reqLen && buffer != 0)
	{
		memcpy(buffer,string->text,reqLen);
	}
		
	return reqLen;
}

static __inline void string_deSerialize(const char* buffer, int len,
					StringType* string)
{
	if (buffer[0] == 0)
	{
		string_initInstance(string);
	}
	else
	{
		string_charAssign(string,buffer);		
	}
}
