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

#ifndef INCLUDED_EXPRESSION_H
#define INCLUDED_EXPRESSION_H

#include "env.h"
#include "slist.h"

struct expression_s_t;
typedef struct expression_s_t* expression_t;

expression_t expression_create_empty();

expression_t expression_create_const(double val);

expression_t expression_create_var(const char* vname);

expression_t expression_create_fun(const char* fname, slist_t args);

expression_t expression_create_builtin(void* fun_ptr, slist_t args);

void expression_free(expression_t exp);

/**
 *  0 = success
 * -1 = unknown variable
 * -2 = unknown function
 * -3 = too many arguments (for now only 2 are allowed)
 */
int expression_eval(expression_t exp, venv_t venv, fenv_t fenv,
                    double* result);
#endif
