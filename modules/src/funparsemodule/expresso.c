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

#include "expresso.h"

#include <stdlib.h>

#include "parser.h"
#include "expression.h"

struct exp_s_t
{
  expression_t e;
};

exp_t exp_create()
{
  exp_t exp = (exp_t) malloc(sizeof(*exp));
  exp->e = expression_create_empty();

  return exp;
}

void exp_free(exp_t exp)
{
  expression_free(exp->e);
  free(exp);
}

/**
 * returns 1 on success, 0 on failure
 */
int exp_parse(exp_t exp, const char* exp_string)
{
  int result = parse_expression(&exp->e, exp_string);
  if (!result)
    return 0;
  else
    return 1;
}

int exp_eval(exp_t exp, venv_t venv, fenv_t fenv, double* result)
{
  return expression_eval(exp->e, venv, fenv, result);
}
