
#include <string.h>
//#include "dlltype.h"

#include "fonttype.h"

int init(void)
{
	return 1;
}

const char* getSpec(void)
{
	return "typ_spec { name=typ_FontType; }";
}

void* newInstance(void)
{
	return font_newInstance();
}

void assign(void* dst,const void* src)
{
	font_assign((FontType*) dst, (const FontType*) src);
}

void deleteInstance(void* num)
{
	font_deleteInstance((FontType*) num);
}

int serialize(void* type, char* buffer, int bufferLen)
{
	return 0;
}

void deSerialize(const char* buffer, int len, void* type)
{
	font_deSerialize(buffer, len, (FontType*) type);
//	return 0;
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Font }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}


