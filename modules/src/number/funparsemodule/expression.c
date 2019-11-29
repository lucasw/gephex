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

#include "expression.h"

#include <stdlib.h>
#include <assert.h>

#include "string_copy.h"


typedef double (*exp_eval_t)(expression_t exp, venv_t, fenv_t);

typedef double (*fun0_t)();
typedef double (*fun1_t)(double);
typedef double (*fun2_t)(double, double);
typedef double (*fun3_t)(double, double, double);
typedef double (*fun4_t)(double, double, double, double);

struct expression_s_t
{
  exp_eval_t eval;

  slist_t args;
  char*  name;
  double immediate;
  fun_t fptr;
  int status;
};


double nop_eval(expression_t exp, venv_t venv, fenv_t fenv)
{
  return 0;
}

double const_eval(expression_t exp, venv_t venv, fenv_t fenv)
{
  return exp->immediate;
}

double var_eval(expression_t exp, venv_t venv, fenv_t fenv)
{
  double value;
  int result = venv_lookup(venv, exp->name, &value);

  if (result == 0)
    {
      exp->status = -1;
      return 0;
    }
  else
    {
      return value;
    }
}

#define EXPR_MAX_ARGS 4
int exec_fun(fun_t fun, slist_t args, 
             venv_t venv, fenv_t fenv, double* result)
{
  double arg_values[EXPR_MAX_ARGS];
  slist_iterator_t it;
  int index;
  int arity = slist_size(args);

  if (arity > EXPR_MAX_ARGS)
    {
      return -3;
    }

  index = 0;
  it = slist_begin(args);
  while ( it != slist_end(args) )
    {
      expression_t arg = (expression_t) slist_iter_deref(it);

      arg_values[index] = arg->eval(arg, venv, fenv);
      if (arg->status != 0)
        {
          return arg->status;
        }

      slist_iter_advance(&it);
      index++;
    }
  
  switch (arity)
    {
    case 0:
      {
        fun0_t f = (fun0_t) fun;
        *result = f();
        return 1;
      } break;
    case 1:
      {
        fun1_t f = (fun1_t) fun;
        *result = f(arg_values[0]);
        return 1;
      } break;
    case 2:
      {
        fun2_t f = (fun2_t) fun;
        *result = f(arg_values[0], arg_values[1]);
        return 1;
      } break;
    case 3:
      {
        fun3_t f = (fun3_t) fun;
        *result = f(arg_values[0], arg_values[1], arg_values[2]);
        return 1;
      } break;
    case 4:
      {
        fun4_t f = (fun4_t) fun;
        *result = f(arg_values[0], arg_values[1],
                    arg_values[2], arg_values[3]);
        return 1;
      } break;
    default:
      assert(!"Fix me");
      return 0;
    }
}

double fun_eval(expression_t exp, venv_t venv, fenv_t fenv)
{
  fun_t fun;
  int arity  = slist_size(exp->args);
  int result = fenv_lookup(fenv, exp->name, arity, &fun);
  double r;

  if (result == 0)
    {
      exp->status = -2;
      return 0;
    }

  result = exec_fun(fun, exp->args, venv, fenv, &r);

  if (result < 0)
    {
      exp->status = result;
      return 0;
    }

  return r;
}

double builtin_eval(expression_t exp, venv_t venv, fenv_t fenv)
{
  fun_t fun = exp->fptr;
  double r;
  int result = exec_fun(fun, exp->args, venv, fenv, &r);

  if (result < 0)
    {
      exp->status = result;
      return 0;
    }

  return r;
}

expression_t expression_create(exp_eval_t eval,
                               slist_t args,
                               const char* name,
                               double immediate,
                               fun_t fptr)
{
  expression_t exp = (expression_t) malloc(sizeof(*exp));
  
  exp->eval = eval;
  exp->args = args;
  exp->name = string_copy(name);
  exp->immediate = immediate;
  exp->fptr = fptr;
  exp->status = 0;

  return exp;
}

void expression_free(expression_t exp)
{
  if (exp->args)
    slist_free(exp->args);

  if (exp->name)
    free(exp->name);
}

expression_t expression_create_empty()
{
  return expression_create(nop_eval, 0, 0, 0, 0);
}

expression_t expression_create_const(double val)
{
  return expression_create(const_eval, 0, 0, val, 0);
}

expression_t expression_create_var(const char* vname)
{
  return expression_create(var_eval, 0, vname, 0, 0);
}

expression_t expression_create_fun(const char* fname, slist_t args)
{
  return expression_create(fun_eval, args, fname, 0, 0);
}

expression_t expression_create_builtin(void* fun_ptr, slist_t args)
{
  return expression_create(builtin_eval, args, 0, 0, fun_ptr);
}

int expression_eval(expression_t exp, venv_t venv, fenv_t fenv, double* result)
{
  double r;

  exp->status = 0;

  r = exp->eval(exp, venv, fenv);

  if (exp->status != 0)
    {
      return exp->status;
    }

  *result = r;
  return 0;
}
