#include "ifstype.h"

#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_IfsType; }";
}

TypeInstanceID newInstance(void)
{
  return ifs_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  ifs_assign((IfsType*)dst,(const IfsType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  ifs_deleteInstance((IfsType*) num);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=IFS }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
