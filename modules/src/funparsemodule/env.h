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

#ifndef INCLUDED_ENV_H
#define INCLUDED_ENV_H

typedef void* venv_t;
typedef void* fenv_t;

typedef double (*fun_t)();


venv_t venv_create();
void venv_free(venv_t venv);
void venv_update(venv_t venv, const char* name, double value);
int venv_lookup(const venv_t venv, const char* name, double* value);

fenv_t fenv_create();
void fenv_free(fenv_t fenv);
void fenv_update(fenv_t fenv, const char* name, int arity, fun_t value);
int fenv_lookup(const fenv_t fenv, const char* name,
                int arity, fun_t* value);

#endif
