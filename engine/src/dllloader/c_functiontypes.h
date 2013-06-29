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

#ifndef INCLUDED_FUNCTION_TYPES_H
#define INCLUDED_FUNCTION_TYPES_H

typedef int (*initT)(void (*)(int,const char*,const char*));
typedef void (*shutDownT)();

typedef void*  (*newInstanceT) ();

typedef const char* (*getSpecT) (void);
typedef const char* (*getInputSpecT) (int);
typedef const char* (*getOutputSpecT) (int);
typedef int (*getInfoT)(char* ,int);

typedef void (*deleteInstanceT) (void* instance);
typedef int (*setInputT) (void* instance,int index,void* typePointer);
typedef int (*setOutputT) (void* instance,int index,void* typePointer);
typedef void (*updateT) (void* instance);

typedef void (*parseInputT)(void* ,const char* ,int);
typedef void (*strongDependenciesCalculatedT)(void* ,int** );
typedef void (*getPatchLayoutT)(void* instance, int** out2in);

typedef void* (*getInputAttributesT)(int);

typedef void (*assignT)(void*,const void*);
typedef int (*serializeT)(void* type, char* buffer, int bufferLen);
typedef void (*deSerializeT)(const char* buffer,int len, void*);
typedef int (*attributesEqualT)(void*,void*);	
typedef int (*convertTypeT)(void*,void*,void*);
			  
#endif
