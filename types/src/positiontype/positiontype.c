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

// Liefert Informationen �ber den Typ zurueck.
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
