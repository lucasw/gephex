#include "miditype.h"

//#include <string.h>
#include "dlltype.h"

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_MidiType; }";
}

TypeInstanceID newInstance(void)
{
  return midi_newInstance();
}

void assign(TypeInstanceID dst,TypeInstanceID src)
{
  midi_assign((MidiType*)dst,(const MidiType*)src);
}

void deleteInstance(TypeInstanceID num)
{
  midi_deleteInstance((MidiType*) num);
}

int serialize(TypeInstanceID type, char* buffer, int bufferLen)
{
	return midi_serialize((MidiType*)type,buffer,bufferLen);
}

void deSerialize(const char* buffer, int len,TypeInstanceID type)
{
   MidiType* pos = (MidiType*) type;
    midi_deSerialize(buffer,len,pos);
}

void shutDown(void)
{
}

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=Midi }";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}
