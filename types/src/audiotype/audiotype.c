#include "audiotype.h"

//#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_AudioType; }";
}

TypeInstanceID newInstance(void)
{
  return audio_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  audio_assign((AudioType*)dst,(const AudioType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  audio_deleteInstance((AudioType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
	return audio_serialize((AudioType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
{
   AudioType* pos = (AudioType*) type;
    audio_deSerialize(buffer,len,pos);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Audio }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
