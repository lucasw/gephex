#include "lfotype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_LfoType; }";
}

TypeInstanceID newInstance(void)
{
  return lfo_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  lfo_assign((LfoType*)dst,(const LfoType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  lfo_deleteInstance((LfoType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
	return lfo_serialize((LfoType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
{
  LfoType* lfo = (LfoType*) type;
  lfo_deSerialize(buffer,len,lfo);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Lfo }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
