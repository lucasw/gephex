#include "positiontype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_PositionType; }";
}

TypeInstanceID newInstance(void)
{
  return pos_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  pos_assign((PositionType*)dst,(const PositionType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  pos_deleteInstance((PositionType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
	return pos_serialize((PositionType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
{
  PositionType* pos = (PositionType*) type;
  pos_deSerialize(buffer,len,pos);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Position }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
