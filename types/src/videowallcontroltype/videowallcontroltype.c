#include "videowallcontroltype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_VideowallControlType; }";
}

void* newInstance(void)
{
  return videowallcontrol_newInstance();
}

void assign(void* dst,const void* src)
{
  videowallcontrol_assign((VideoWallControlType*)dst,(const VideoWallControlType*)src);
}

void deleteInstance(void* num)
{
  videowallcontrol_deleteInstance((VideoWallControlType*) num);
}

int serialize(void* type, char* buffer, int bufferLen)
{
	return videowallcontrol_serialize((VideoWallControlType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,void* type)
{
  VideoWallControlType* videowallcontrol = (VideoWallControlType*) type;
  videowallcontrol_deSerialize(buffer,len,videowallcontrol);

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
