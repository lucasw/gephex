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

#include <stdlib.h>
#include <string.h>

// Zahl von 0 bis (2^32)-1
typedef struct StringType_
{
	char* text;
} StringType;

static __inline void string_charAssign(StringType* dst,const char* src)
{
	int lens = strlen(src)+1;
	if (dst->text != 0)
		free(dst->text);

	dst->text = (char*) malloc(lens);
	memcpy(dst->text,src,lens);
}


static __inline void string_initInstance(StringType* newString)
{
	newString->text = 0;
	string_charAssign(newString,"null");	
}

static __inline StringType* string_newInstance(void)
{
	StringType* newType = (StringType*) malloc(sizeof(StringType));	

	string_initInstance(newType);
	return newType;
}

static __inline void string_assign(StringType* dst,const StringType* src)
{
	string_charAssign(dst,src->text);
}

static __inline void string_destroyInstance(StringType* num)
{
   free(num->text);
}

static __inline void string_deleteInstance(StringType* num)
{
	string_destroyInstance(num);
	free(num);
}

static __inline int string_serialize(const StringType* string, char* buffer,
				     int bufferLen)
{
	int reqLen = strlen(string->text) + 1;

	if (bufferLen >= reqLen && buffer != 0)
	{
		memcpy(buffer,string->text,reqLen);
	}
		
	return reqLen;
}

static __inline void string_deSerialize(const char* buffer, int len,
					StringType* string)
{
	if (buffer[0] == 0)
	{
		string_initInstance(string);
	}
	else
	{
		string_charAssign(string,buffer);		
	}
}
