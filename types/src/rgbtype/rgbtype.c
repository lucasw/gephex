#include "rgbtype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_RGBType; }";
}

void* newInstance(void)
{
  return rgb_newInstance();
}

void assign(void* dst,const void* src)
{
  rgb_assign((RGBType*)dst,(const RGBType*)src);
}

void deleteInstance(void* rgb)
{
  rgb_deleteInstance((RGBType*) rgb);
}

int serialize(void* type, char* buffer, int bufferLen)
{
  return rgb_serialize((RGBType*)type, buffer, bufferLen);
}

void deSerialize(const char* buffer,int len, void* type)
{
  rgb_deSerialize(buffer,len,(RGBType*) type);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Farbe }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}


