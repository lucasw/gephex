/* Simple Number Arithmetics
  Copyright (C) 2003 Martin Bayer, Georg Seidel, Philipp Promesberger
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
      
  You can reach me via email: georg.seidel@web.de
*/

#include "numarithmodule.h"

#include <assert.h>
#include <math.h>

static logT s_log;

//---------------------------------------------------------------------------

typedef double (*operation_t)(double lhs, double rhs);

static double add_op(double lhs, double rhs);
static double sub_op(double lhs, double rhs);
static double mul_op(double lhs, double rhs);
static double div_op(double lhs, double rhs);
static double mod_op(double lhs, double rhs);
static double pow_op(double lhs, double rhs);
static double max_op(double lhs, double rhs);
static double min_op(double lhs, double rhs);
static double exp_op(double lhs, double rhs);
static double ln_op(double lhs, double rhs);
static double sin_op(double lhs, double rhs);
static double abs_op(double lhs, double rhs);
static double proj1_op(double lhs, double rhs);
static double proj2_op(double lhs, double rhs);
static double floor_op(double lhs, double rhs);
static double ceil_op(double lhs, double rhs);
static double round_op(double lhs, double rhs);

//---------------------------------------------------------------------------

typedef struct _MyInstance {

  operation_t op;

  StringType op_text;

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

  my->op = 0;
  string_initInstance(&my->op_text);

  return my;
}

void destruct(MyInstance* my)
{
  string_destroyInstance(&my->op_text);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst    = (InstancePtr) instance;
  MyInstancePtr my    = inst->my;
  const char* op_text = inst->in_op->text;

  if (strcmp(my->op_text.text, op_text) != 0
      || my->op == 0)
    {
      string_assign(&my->op_text, inst->in_op);
	  
      if (strcmp(op_text, "x+y") == 0) {
        my->op = add_op;
      }
      else if (strcmp(op_text, "x-y") == 0) {
        my->op = sub_op;
      }
      else if (strcmp(op_text, "x*y") == 0) {
        my->op = mul_op;
      }
      else if (strcmp(op_text, "x/y") == 0) {
        my->op = div_op;
      }
      else if (strcmp(op_text, "x%y") == 0) {
        my->op = mod_op;
      }
      else if (strcmp(op_text, "x^y") == 0) {
        my->op = pow_op;
      }
      else if (strcmp(op_text, "max(x;y)") == 0) {
        my->op = max_op;
      }
      else if (strcmp(op_text, "min(x;y)") == 0) {
        my->op = min_op;
      }
      else if (strcmp(op_text, "exp(x)") == 0) {
        my->op = exp_op;
      }
      else if (strcmp(op_text, "ln(x)") == 0) {
        my->op = ln_op;
      }
      else if (strcmp(op_text, "sin(x)") == 0) {
        my->op = sin_op;
      }
      else if (strcmp(op_text, "|x|") == 0) {
        my->op = abs_op;
      }
      else if (strcmp(op_text, "x") == 0) {
        my->op = proj1_op;
      }
      else if (strcmp(op_text, "y") == 0) {
        my->op = proj2_op;
      }
      else if (strcmp(op_text, "floor(x)") == 0) {
        my->op = floor_op;
      }
      else if (strcmp(op_text, "ceil(x)") == 0) {
        my->op = ceil_op;
      }
      else if (strcmp(op_text, "round(x)") == 0) {
        my->op = round_op;
      }
      else {
        char buffer[128];
        snprintf(buffer, sizeof(buffer),
                 "Unknown operation: '%s' - using x+y instead!",
                 op_text);
        s_log(0, buffer);
        my->op = add_op;
      }
    }

  assert(my->op);

  inst->out_r->number = my->op(inst->in_lhs->number, inst->in_rhs->number);
}

//---------------------------------------------------------------------------

static double add_op(double lhs, double rhs) {
  return lhs + rhs;
}

static double sub_op(double lhs, double rhs) {
  return lhs - rhs;
}

static double mul_op(double lhs, double rhs) {
  return lhs * rhs;
}

static double div_op(double lhs, double rhs) {
  if (fabs(rhs) < 0.00000001)
    return 0;

  return lhs / rhs;
}

static double mod_op(double lhs, double rhs) {
  if (fabs(rhs) < 0.0000000001)
    return 0;
  else
    return fmod(lhs,rhs);
}

static double pow_op(double lhs, double rhs) {
  return pow(lhs, rhs);
}

static double max_op(double lhs, double rhs) {
  return (lhs > rhs) ? lhs : rhs;
}

static double min_op(double lhs, double rhs) {
  return (lhs < rhs) ? lhs : rhs;
}

static double exp_op(double lhs, double rhs) {
  return exp(lhs);
}

static double ln_op(double lhs, double rhs) {
  return log(lhs);
}

static double sin_op(double lhs, double rhs) {
  return sin(lhs);
}

static double abs_op(double lhs, double rhs) {
  return fabs(lhs);
}

static double proj1_op(double lhs, double rhs) {
  return lhs;
}

static double proj2_op(double lhs, double rhs) {
  return rhs;
}

static double floor_op(double lhs, double rhs) {
  return floor(lhs);
}

static double ceil_op(double lhs, double rhs) {
  return ceil(lhs);
}

static double round_op(double lhs, double rhs) {
  return floor(rhs+0.5);
}
