/* Simple Expression Parser Module
  Copyright (C) 2004 Martin Bayer, Georg Seidel, Philipp Promesberger
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de */

#include "funparsemodule.h"

#include <assert.h>
#include <math.h>

#include "expresso.h"

static logT s_log;

static const char* default_exp = "0";

//---------------------------------------------------------------------------

static double max_op(double lhs, double rhs);
static double min_op(double lhs, double rhs);
static double max3_op(double a, double b, double c);
static double min3_op(double a, double b, double c);
static double max4_op(double a, double b, double c, double d);
static double min4_op(double a, double b, double c, double d);
static double exp_op(double lhs);
static double ln_op(double lhs);
static double sin_op(double lhs);
static double cos_op(double lhs);

static double floor_op(double lhs);
static double ceil_op(double lhs);
static double round_op(double lhs);


//---------------------------------------------------------------------------

typedef struct _MyInstance {

  venv_t venv;
  fenv_t fenv;
  exp_t exp;

  StringType exp_text;

  int used_vars[4];

} MyInstance, *MyInstancePtr;

//---------------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
    {
      s_log(0, "Could not allocate memory for MyInstance struct\n");
      return 0;
    }

  my->venv = venv_create();
  my->fenv = fenv_create();
  my->exp  = exp_create();

  string_initInstance(&my->exp_text);

  my->used_vars[0] = 0;
  my->used_vars[1] = 0;
  my->used_vars[2] = 0;
  my->used_vars[3] = 0;

  fenv_update(my->fenv, "max", 2,  (fun_t) max_op);
  fenv_update(my->fenv, "min", 2,  (fun_t) min_op);
  fenv_update(my->fenv, "max", 3,  (fun_t) max3_op);
  fenv_update(my->fenv, "min", 3,  (fun_t) min3_op);
  fenv_update(my->fenv, "max", 4,  (fun_t) max4_op);
  fenv_update(my->fenv, "min", 4,  (fun_t) min4_op);
  fenv_update(my->fenv, "exp", 1,  (fun_t) exp_op);
  fenv_update(my->fenv, "ln",  1,  (fun_t) ln_op);
  fenv_update(my->fenv, "sin", 1,  (fun_t) sin_op);
  fenv_update(my->fenv, "cos", 1,  (fun_t) cos_op);
  fenv_update(my->fenv, "floor", 1, (fun_t) floor_op);
  fenv_update(my->fenv, "ceil",  1, (fun_t) ceil_op);
  fenv_update(my->fenv, "round", 1, (fun_t) round_op);

  return my;
}

void destruct(MyInstance* my)
{
  venv_free(my->venv);
  fenv_free(my->fenv);
  exp_free(my->exp);

  string_destroyInstance(&my->exp_text);
  free(my);
}

static int is_prefix(const char* sub, const char* str)
{
  unsigned int l_sub = strlen(sub);
  unsigned int l_str = strlen(str);

  if (l_sub > l_str)
    return 0;

  if (l_sub == 0)
    return 1;

  assert(l_sub > 0 && l_str > 0);

  if (sub[0] == str[0])
    return is_prefix(sub+1, str+1);
  else
    return 0;
}

static int is_substr(const char* sub, const char* str)
{
  unsigned int l_str = strlen(str);

  if (is_prefix(sub, str))
    return 1;

  if (l_str > 0)
    return is_substr(sub, str+1);

  return 0;
}

void strongDependencies(Instance* inst, int neededInputs[])
{
  MyInstancePtr my = inst->my;
  const char* expr = inst->in_exp->text;

  if (!is_substr("x1", expr))
    {
      neededInputs[in_x1] = 0;
      my->used_vars[0]    = 0;
    }
  else
    {
      my->used_vars[0] = 1;
    }

  if (!is_substr("x2", expr))
    {
      neededInputs[in_x2] = 0;
      my->used_vars[1]    = 0;
    }
  else
    {
      my->used_vars[1] = 1;
    }

  if (!is_substr("x3", expr))
    {
      neededInputs[in_x3] = 0;
      my->used_vars[2]    = 0;
    }
  else
    {
      my->used_vars[2] = 1;
    }

  if (!is_substr("x4", expr))
    {
      neededInputs[in_x4] = 0;
      my->used_vars[3]    = 0;
    }
  else
    {
      my->used_vars[3] = 1;
    }
}

void update(void* instance)
{
  InstancePtr inst    = (InstancePtr) instance;
  MyInstancePtr my    = inst->my;
  const char* exp_text = inst->in_exp->text;
  int result;

  if (strcmp(my->exp_text.text, exp_text) != 0)
    {
      int result;
      string_assign(&my->exp_text, inst->in_exp);
      result = exp_parse(my->exp, exp_text);

      if (result == 0)
        {
          char buffer[128];
          snprintf(buffer, sizeof(buffer),
                   "Invalid expression: '%s' - using '%s' instead!",
                   exp_text, default_exp);
          s_log(0, buffer);
          exp_parse(my->exp, default_exp);
        }
    }

  if (my->used_vars[0])
    venv_update(my->venv, "x1", inst->in_x1->number);

  if (my->used_vars[1])
    venv_update(my->venv, "x2", inst->in_x2->number);

  if (my->used_vars[2])
    venv_update(my->venv, "x3", inst->in_x3->number);

  if (my->used_vars[3])
    venv_update(my->venv, "x4", inst->in_x4->number);

  result = exp_eval(my->exp, my->venv, my->fenv, &inst->out_r->number);
  
  if (result != 0)
    {
      char buffer[128];
      snprintf(buffer, sizeof(buffer),
               "Error executing: '%s' - using '%s' instead!",
               exp_text, default_exp);
      s_log(0, buffer);
      exp_parse(my->exp, default_exp);
    }
}

//---------------------------------------------------------------------------


static double max_op(double lhs, double rhs) {
  return (lhs > rhs) ? lhs : rhs;
}

static double min_op(double lhs, double rhs) {
  return (lhs < rhs) ? lhs : rhs;
}

static double max3_op(double a, double b, double c) {
  return max_op(a, max_op(b, c));
}

static double min3_op(double a, double b, double c) {
  return min_op(a, min_op(b, c));
}

static double max4_op(double a, double b, double c, double d) {
  return max_op(a, max3_op(b, c, d));
}

static double min4_op(double a, double b, double c, double d) {
  return min_op(a, min3_op(b, c, d));
}

static double exp_op(double lhs) {
  return exp(lhs);
}

static double ln_op(double lhs) {
  return log(lhs);
}

static double sin_op(double lhs) {
  return sin(lhs);
}

static double cos_op(double lhs) {
  return cos(lhs);
}

static double floor_op(double lhs) {
  return floor(lhs);
}

static double ceil_op(double lhs) {
  return ceil(lhs);
}

static double round_op(double lhs) {
  return floor(lhs+0.5);
}

//---------------------------------------------------------------------------
