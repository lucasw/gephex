#include "framebuffertype.h"

#include "dlltype.h"

typedef TypeInstanceID FrameBufferInstanceID;
typedef TypeAttributesInstanceID FrameBufferAttributesInstanceID;

int init(void)
{
  return 1;
}

const char* getSpec(void)
{
  return "typ_spec { name=typ_FrameBufferType; }";
}

FrameBufferInstanceID newInstance(void)
{
  return framebuffer_newInstance();
}

void assign(FrameBufferInstanceID dst, FrameBufferInstanceID src)
{
  framebuffer_assign((FrameBufferType*)dst,(FrameBufferType*)src);
}

void deleteInstance(FrameBufferInstanceID num)
{
  framebuffer_deleteInstance((FrameBufferType*) num);
}

int serialize(FrameBufferInstanceID type, char* buffer, int bufferLen)
{
  return framebuffer_serialize(type, buffer, bufferLen);
}

void deSerialize(const char* buffer, int len, FrameBufferInstanceID type)
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


int attributesEqual(FrameBufferInstanceID type_, 
		    FrameBufferAttributesInstanceID attributes_)
{
  FrameBufferType* type = (FrameBufferType*) type_;
  FrameBufferAttributes* attributes = (FrameBufferAttributes*) attributes_;

  return framebuffer_attributesEqual(type, attributes);
}


int convertType(FrameBufferInstanceID dstType_,
		 FrameBufferInstanceID srcType_, 
		 FrameBufferAttributesInstanceID attributes_)
{
  return framebuffer_convertType((FrameBufferType*) dstType_,
			  (const FrameBufferType*) srcType_,
			  (FrameBufferAttributes*) attributes_);	
}

int changeAttributes(FrameBufferInstanceID fb_, 
		      FrameBufferAttributesInstanceID attributes_)
{
  return framebuffer_changeAttributes((FrameBufferType*) fb_,
			       (FrameBufferAttributes*) attributes_);
}
