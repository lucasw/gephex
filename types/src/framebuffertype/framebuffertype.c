#include "framebuffertype.h"

#include "dlltype.h"

int init(void)
{
	return 1;
}

const char* getSpec(void)
{
	return "typ_spec { name=typ_FrameBufferType; }";
}

void* newInstance(void)
{
	return framebuffer_newInstance();
}

void assign(void* dst,const void* src)
{
	framebuffer_assign((FrameBufferType*)dst,(FrameBufferType*)src);
}

void deleteInstance(void* num)
{
	framebuffer_deleteInstance((FrameBufferType*) num);
}

int serialize(void* type, char* buffer, int bufferLen)
{
  return framebuffer_serialize(type, buffer, bufferLen);
}

void deSerialize(const char* buffer, int len, void* type)
{
  framebuffer_deSerialize(buffer,len,type);
}

void shutDown(void)
{
}



// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen)
{
  static const char* 
    INFO = "Bild [x:typ_NumberType y:typ_NumberType]";
  int reqLen = strlen(INFO) + 1;
  if (buf != 0 && reqLen <= bufLen)
    {
      memcpy(buf,INFO,reqLen);
    }
  return reqLen;
}


int attributesEqual(void* type_, void* attributes_)
{
	FrameBufferType* type = (FrameBufferType*) type_;
	FrameBufferAttributes* attributes = (FrameBufferAttributes*) attributes_;

	return framebuffer_attributesEqual(type, attributes);
}


void convertType(void* dstType_,void* srcType_, void* attributes_)
{
	framebuffer_convertType((FrameBufferType*) dstType_,
						    (FrameBufferType*) srcType_,
							(FrameBufferAttributes*) attributes_);	
}

void changeAttributes(void* fb_, void* attributes_)
{
	framebuffer_changeAttributes((FrameBufferType*) fb_,
								 (FrameBufferAttributes*) attributes_);
}
