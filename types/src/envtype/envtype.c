#include "envtype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_EnvType; }";
}

TypeInstanceID newInstance(void)
{
  return env_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  env_assign((EnvType*)dst,(const EnvType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  env_deleteInstance((EnvType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
	return env_serialize((EnvType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
{
  EnvType* env = (EnvType*) type;
  env_deSerialize(buffer,len,env);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Env }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
