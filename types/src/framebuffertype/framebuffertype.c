/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
