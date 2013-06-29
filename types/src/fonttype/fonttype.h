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
#include <stdio.h>
#include <string.h>
#include <windows.h>

//Font Weights
/*#define	FW_DONTCARE 0 
#define FW_THIN 100 
#define FW_EXTRALIGHT 200 
#define FW_ULTRALIGHT 200 
#define FW_LIGHT 300 
#define FW_NORMAL 400 
#define FW_REGULAR 400 
#define FW_MEDIUM 500 
#define FW_SEMIBOLD 600 
#define FW_DEMIBOLD 600 
#define FW_BOLD 700 
#define FW_EXTRABOLD 800 
#define FW_ULTRABOLD 800 
#define FW_BLACK 900 
#define FW_HEAVY 900 
*/
// Font (momentan windows fonts...)
typedef struct FontType_
{
	char* name;
	int width;
	int height;
	int weight;
	BOOL italic;
	BOOL underline;

} FontType;
		
static __inline void font_initInstance(FontType* font)
{
	if (font->name != 0)
		free(font->name);

	font->name = malloc(1);
	strcpy(font->name,"");
	font->height = 0;
	font->width = 0;
	font->italic = FALSE;
	font->underline = FALSE;
}

static __inline FontType* font_newInstance(void)
{
	FontType* newType = (FontType*) malloc(sizeof(FontType));
	newType->name = 0;

	font_initInstance(newType);
	
	return newType;
}

static __inline void font_assign(FontType* dst,const FontType* src)
{
	int lens = strlen(src->name)+1;
	if (dst->name != 0)
		free(dst->name);

	dst->name = (char*)malloc(lens);
	memcpy(dst->name,src->name,lens);
	
	dst->height    = src->height;	
	dst->width     = src->width;
	dst->weight    = src->weight;
	dst->italic    = src->italic;
	dst->underline = src->underline;

}

static __inline void font_deleteInstance(FontType* font)
{
	if (font->name)
		free(font->name);
	free(font);
}

static __inline int font_serialize(FontType* font, char* buffer, int bufferLen)
{
	int reqLen = strlen(font->name) + 3 + 7*3 + 6*2;

	if (bufferLen >= reqLen && buffer != 0)
	{
		const char* italic = (font->italic == 0) ? "false" : "true";
		const char* underline = (font->underline == 0) ? "false" : "true";
		sprintf(buffer,"{%s} %d %d %d %s %s",font->name,font->width,
				font->height,font->weight,italic,underline);
	}

	return reqLen;
}

static __inline void font_deSerialize(const char* buffer, int len, FontType* font)
{
	int index = 0;
	int pos1, pos2;
	char italic[10];
	char underline[10];

	if (buffer[0] == 0)
	{
		font_initInstance(font);
	}
	else
	{

	for (; index < len; ++index)
	{
		if (buffer[index] == '{')
			break;
	}
	if (index == len)
	{
		//FEHLER, keine oeffnende klammer
		return;
	}
	pos1 = index +1 ;

	for (index = pos1; index < len; ++index)
	{
		if (buffer[index] == '}')
			break;
	}
	if (index == len)
	{
		//FEHLER, keine oeffnende klammer
		return;
	}
	pos2 = index;

	if (font->name != 0)
		free(font->name);

	font->name = (char*) malloc(pos2-pos1 + 1);
	memcpy(font->name,buffer + pos1,pos2-pos1);
	font->name[pos2-pos1] = 0;

	

	sscanf(buffer+pos2+1,"%d %d %d %s %s",&font->width, &font->height,
							           &font->weight, italic, underline);

	if(strcmp(italic, "false")==0)
	{
		font->italic = 0;
	}
	else if(strcmp(italic, "true")==0)
	{
		font->italic = 1;
	}

	if(strcmp(underline, "false")==0)
	{
		font->underline = 0;
	}
	else if(strcmp(underline, "true")==0)
	{
		font->underline = 1;
	}
	}
//	return 0;
}
