#include <string.h>
#include "dlltype.h"

#include "stringtype.h"

int init(void)
{
	return 1;
}

const char* getSpec(void)
{
	return "typ_spec { name=typ_StringType; }";
}

void* newInstance(void)
{
	return string_newInstance();
}

void assign(void* dst,const void* src)
{
	string_assign((StringType*) dst, (const StringType*) src);
}

void deleteInstance(void* num)
{
	string_deleteInstance((StringType*) num);
}

int serialize(void* type, char* buffer, int bufferLen)
{
	return string_serialize((StringType*) type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len, void* type)
{
	string_deSerialize(buffer,len,(StringType*)type);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Zeichenfolge }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}


