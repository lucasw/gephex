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

#include "env.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#if defined (_MSC_VER)
#define snprintf _snprintf
#endif

#include "string_copy.h"
#include "slist.h"

//-------------------------------------------------------------------------

typedef void (*value_free_t)(void*);

struct env_s_t
{
  slist_t pairs;

  value_free_t value_free;
};

typedef struct env_s_t* env_t;

struct envpair_s_t
{
  char* name;
  void* value;

  value_free_t value_free;
};

typedef struct envpair_s_t* envpair_t;

envpair_t envpair_create(const char* name, void* value,
                         value_free_t value_free)
{
  envpair_t p = (envpair_t) malloc(sizeof(*p));

  p->name       = string_copy(name);
  p->value      = value;
  p->value_free = value_free;

  return p;
}

void envpair_free(envpair_t ep)
{
  free(ep->name);
  ep->value_free(ep->value);

  free(ep);
}

env_t env_create(value_free_t value_free)
{
  env_t e = (env_t) malloc(sizeof(*e));
  e->pairs      = slist_create();
  e->value_free = value_free;

  return e;
}

void env_free(env_t e)
{
  slist_iterator_t it = slist_begin(e->pairs);

  for (; it != slist_end(e->pairs); slist_iter_advance(&it))
    {
      envpair_t p = (envpair_t) slist_iter_deref(it);
      envpair_free(p);
    }
  
  slist_free(e->pairs);
  free(e);
}

int name_equals(void* p_, void* closure)
{
  envpair_t p = (envpair_t) p_;
  const char* name = (const char*) closure;

  if (strcmp(p->name, name) == 0)
    return 1;
  else
    return 0;
}

void env_update(env_t e, const char* name, void* value)
{
  slist_iterator_t it = slist_find_if(e->pairs, name_equals, (void*) name);
  if (it == slist_end(e->pairs))
    {
      envpair_t p = envpair_create(name, value, e->value_free);
      slist_push_front(e->pairs, p);
    }
  else
    {
      envpair_t p = (envpair_t) slist_iter_deref(it);
      e->value_free(p->value);
      p->value = value;
    }
}

int env_lookup(env_t e, const char* name, void** value)
{
  slist_iterator_t it = slist_find_if(e->pairs, name_equals, (void*) name);

  if (it == slist_end(e->pairs))
    {
      return 0;
    }
  else
    {
      envpair_t p = (envpair_t) slist_iter_deref(it);
      *value = p->value;
      return 1;
    }
}

//-------------------------------------------------------------------------

static void var_value_free(void* value)
{
  double* v = (double*) value;
  free(v);
}

venv_t venv_create()
{
  return (venv_t*) env_create(var_value_free);
}

void venv_free(venv_t venv)
{
  env_free((env_t) venv);
}

void venv_update(venv_t venv, const char* name, double value)
{
  double* v = malloc(sizeof(*v));
  *v = value;
  env_update((env_t) venv, name, v);
}

int venv_lookup(const venv_t venv, const char* name, double* value)
{
  double* v;
  int result =  env_lookup((env_t) venv, name, (void**) &v);

  if (result == 0)
    return 0;

  *value = *v;
  return 1;
}

//-------------------------------------------------------------------------

struct fun_desc_s_t
{
  fun_t ptr;
};

typedef struct fun_desc_s_t* fun_desc_t;

fun_desc_t fun_desc_create(fun_t ptr)
{
  fun_desc_t fd = (fun_desc_t) malloc(sizeof(*fd));

  fd->ptr   = ptr;

  return fd;
}

void fun_desc_free(fun_desc_t fd)
{
  free(fd);
}

static void fun_value_free(void* val)
{
  fun_desc_t fd = (fun_desc_t) val;
  fun_desc_free(fd);
}

fenv_t fenv_create()
{
  return (fenv_t) env_create(fun_value_free);
}

void fenv_free(fenv_t fenv)
{
  env_free((env_t) fenv);
}

static void mangle_fun_name(char* dst, unsigned int dst_size,
                            const char* name, int arity)
{
  assert(arity <= 99 && strlen(name) < dst_size - 6);

  snprintf(dst, dst_size, "%s_#%i", name, arity);
}

void fenv_update(fenv_t fenv, const char* name, int arity, fun_t value)
{
  char buffer[1024];
  fun_desc_t fd;

  mangle_fun_name(buffer, sizeof(buffer), name, arity);

  fd = fun_desc_create(value);
  env_update((env_t) fenv, buffer, fd);
}

int fenv_lookup(const fenv_t fenv, const char* name,
                int arity, fun_t* value)
{
  char buffer[1024];
  fun_desc_t fd;
  int result;

  mangle_fun_name(buffer, sizeof(buffer), name, arity);

  result = env_lookup((env_t) fenv, buffer, (void**)&fd);

  if (result == 0)
    return 0;


  *value = fd->ptr;

  return result;
}

//-------------------------------------------------------------------------
