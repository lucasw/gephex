#include "numbertype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_NumberType; }";
}

void* newInstance(void)
{
  return number_newInstance();
}

void assign(void* dst,const void* src)
{
  number_assign((NumberType*)dst,(const NumberType*)src);
}

void deleteInstance(void* num)
{
  number_deleteInstance((NumberType*) num);
}

int serialize(void* type, char* buffer, int bufferLen)
{
	return number_serialize((NumberType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,void* type)
{
  NumberType* number = (NumberType*) type;
  number_deSerialize(buffer,len,number);

}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Zahl }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
