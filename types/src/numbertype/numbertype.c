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

TypeInstanceID newInstance(void)
{
  return number_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  number_assign((NumberType*)dst,(const NumberType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  number_deleteInstance((NumberType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
  return number_serialize((NumberType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
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
