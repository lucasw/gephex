/* Simple Beat Detection
  Copyright (C) 2003 Georg Seidel
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
#include "audiobdmodule.h"

#include <math.h>

static const int HIST_SIZE  = 22050;
static const int LOCAL_SIZE = 1050;

//----------------------------------------------------------------------------

#ifndef _MSC_VER
static int min(int a, int b) {
  return (a < b) ? a : b;
}
static int max(int a, int b) {
  return (a > b) ? a : b;
}
#endif

static logT s_log;

struct bd_instance_t;

struct bd_driver_t {
  struct bd_instance_t* inst;

  struct bd_instance_t* (*create)(int history_size, int local_size);
  void (*destroy)(struct bd_instance_t* sh);
 
  int (*is_beat)(struct bd_instance_t* sh, double* new_samples,
                 int num_samples, double thr);
};

//----------------------------------------------------------------------------

struct bd_expinstance_t {

  int hist_size;
  int local_size;

  double hist_factor;
  double local_factor;

  double hist;
  double local;

  // variance
  double var;
};

static struct bd_instance_t* exp_create(int hist_size, int local_size) {
  struct bd_expinstance_t* sh = malloc(sizeof(*sh));

  if (sh == 0)
    return 0;

  sh->hist_size    = hist_size;
  sh->local_size   = local_size;

  sh->hist_factor  = pow(0.1, 1.0 / ((double) hist_size));
  sh->local_factor = pow(0.1, 1.0 / ((double) local_size));

  //sh->hist_factor  = 0.9999;
  //sh->local_factor = 0.99776;

  sh->hist         = 0;
  sh->local        = 0;
  sh->var          = 0;

  //  printf("hf = %f, lf = %f\n", sh->hist_factor, sh->local_factor);
  return (struct bd_instance_t*) sh;
}

static void exp_destroy(struct bd_instance_t* sh) {
  free(sh);
}

static int exp_is_beat(struct bd_instance_t* sh_, double* samples, int len,
                       double thr)
{
  struct bd_expinstance_t* sh = (struct bd_expinstance_t*) sh_;
  int i;
  double hist         = sh->hist;
  double local        = sh->local;
  double var          = sh->var;
  double hist_size    = (double) sh->hist_size;
  double local_size   = (double) sh->local_size;
  double hist_factor  = sh->hist_factor;
  double local_factor = sh->local_factor;
  double rel;
  //  double hist_avg;

  for (i = 0; i < len; ++i) {
    double s = samples[i] * samples[i];
    hist  = s + hist_factor  * hist;
    local = s + local_factor * local;
  }

  /*  hist_avg = hist / hist_size;
  for (i = 0; i < len; ++i) {
    double s = samples[i] * samples[i] - (hist_avg);

    var   = (s*s) +  hist_factor * var;
    }*/

  rel = local/hist * hist_size / local_size;
  thr += 1.0;// + 6*var / hist_size;

  /*printf("var  = %f\n", var / hist_size);
  printf("thr  = %f\n", thr);
  printf("ding = %f\n", rel);*/

  sh->hist  = hist;
  sh->local = local;
  sh->var   = var;

  if (rel > thr)
    return 1;
  else
    return 0;
}

static struct bd_driver_t* exp_get_driver() {
  struct bd_driver_t* drv = malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->inst = 0;
  drv->create  = exp_create;
  drv->destroy = exp_destroy;
  drv->is_beat = exp_is_beat;

  return drv;
}
//----------------------------------------------------------------------------

struct bd_avinstance_t {

  int hist_buf_size;
  int block_size;
  int raw_size;

  double* hist_buf;
  double* raw_buf;

  int buf_len;
  int raw_len;
};

static struct bd_instance_t* av_create(int hist_size, int local_size)
 {
  struct bd_avinstance_t* sh = malloc(sizeof(*sh));

  if (sh == 0)
    return 0;

  sh->hist_buf_size = hist_size / local_size;
  sh->block_size    = local_size;
  sh->raw_size      = 4*local_size;

  if (sh->hist_buf_size < 1) {
    free(sh);
    return 0;
  }

  sh->hist_buf = malloc(sizeof(double) *  sh->hist_buf_size);
  if (sh->hist_buf == 0) {
    free(sh);
    return 0;
  }

  sh->raw_buf = malloc(sizeof(double) * sh->raw_size);
  if (sh->raw_buf == 0) {
    free(sh->hist_buf);
    free(sh);
    return 0;
  }
  
  sh->raw_len = 0;
  sh->buf_len = 0;

  return (struct bd_instance_t*) sh;
}

static void av_destroy(struct bd_instance_t* sh_) {
  struct bd_avinstance_t* sh = (struct bd_avinstance_t*) sh_;

  free(sh->hist_buf);
  free(sh->raw_buf);
  free(sh);
}

static double calc_energy(double* begin, double* end)
{
  double* i;
  double sum = 0;
  for (i = begin; i != end; ++i) {
    sum += *i * *i;
  }
  return sum;
}


static int av_is_beat(struct bd_instance_t* sh_, double* samples, int len,
                      double thr_)
{
  struct bd_avinstance_t* sh = (struct bd_avinstance_t*) sh_;
  int i;
  int raw_max = min(sh->raw_size - sh->raw_len, len);
  int block_size = sh->block_size;
  int num_blocks;
  double* buf = sh->hist_buf;
  int diff;
  double energy = 0;
  double var = 0;
  double local_energy;
  double thr;

  //  printf("len = %i\n", len);
  //  printf("raw_len = %i\n", sh->raw_len);
  //  printf("raw_max = %i\n", raw_max);
  memcpy(sh->raw_buf + sh->raw_len, samples, raw_max*sizeof(double));
  sh->raw_len += raw_max;

  num_blocks = min(sh->hist_buf_size, sh->raw_len / block_size);

  diff = max(0, (sh->buf_len + num_blocks) - sh->hist_buf_size);
  diff = min(diff, sh->buf_len);

  memmove(buf, buf+diff, (sh->buf_len-diff) * sizeof(double));
  sh->buf_len -= diff;
  for (i = 0; i < num_blocks; ++i) {
    double e = calc_energy(sh->raw_buf + i*block_size, 
                           sh->raw_buf + (i+1)*block_size) / block_size;

    buf[sh->buf_len + i] = e;
  }
  sh->raw_len -= num_blocks*block_size;
  sh->buf_len += num_blocks;

  memmove(sh->raw_buf, sh->raw_buf+num_blocks*block_size, 
          sh->raw_len * sizeof(double));
  //  printf("num_blocks: %i\n", num_blocks);
  //  printf("buffer length: %i\n", sh->buf_len);

  if (sh->buf_len < 0.5*sh->hist_buf_size)
    return 0;

  for (i = 0; i < sh->buf_len; ++i)
    {
      energy += buf[i];
    }
  energy /= ((double) sh->buf_len);
  local_energy = buf[sh->buf_len - 1];

  for (i = 0; i < sh->buf_len; ++i)
    {
      double v = (buf[i] - energy);
      var += v*v;
    }
  var /= ((double) sh->buf_len);

  thr = thr_ + 1.5 - 20*var;
  if (thr < 1)
    thr = 1;
  /*printf("var  = %f\n", var);
   printf("thr  = %f\n", thr);
   printf("ding = %f\n", local_energy / energy);*/

  if (local_energy / energy > thr)
    return 1;
  else
    return 0;
}

static struct bd_driver_t* av_get_driver() {
  struct bd_driver_t* drv = malloc(sizeof(*drv));

  if (drv == 0)
    return 0;

  drv->inst    = 0;
  drv->create  = av_create;
  drv->destroy = av_destroy;
  drv->is_beat = av_is_beat;

  return drv;
}
//----------------------------------------------------------------------------

typedef struct _MyInstance {

  struct bd_driver_t* drv;
  StringType algo;

} MyInstance, *MyInstancePtr;

//----------------------------------------------------------------------------

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

  my->drv = 0;
  string_initInstance(&my->algo);
  return my;
}

void destruct(MyInstance* my)
{
  if (my->drv) {
    if (my->drv->inst) {
      my->drv->destroy(my->drv->inst);
    }
    free(my->drv);
  }
  string_destroyInstance(&my->algo);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int len          = inst->in_audio->len;
  double* samples  = inst->in_audio->samples;
  double thr       = trim_double(inst->in_thr->number, 0, 1);
  int is_beat;

  if (strcmp(my->algo.text, inst->in_algo->text) != 0
      || my->drv == 0)
    {
      string_assign(&my->algo, inst->in_algo);

      if (my->drv) {
        if (my->drv->inst) {
          my->drv->destroy(my->drv->inst);
        }
        free(my->drv);
      }
      
      if (strcmp(inst->in_algo->text, "exp") == 0) {
        my->drv = exp_get_driver();
      }
      else if (strcmp(inst->in_algo->text, "avg") == 0) {
        my->drv = av_get_driver();
      }
      else {
        char buffer[128];
        snprintf(buffer, sizeof(buffer),
                 "Unsupported algo: '%s', using 'exp' instead",
                 my->algo.text);
            
        s_log(0, buffer);
        my->drv = exp_get_driver();
      }

      my->drv->inst = my->drv->create(HIST_SIZE, LOCAL_SIZE);
    }

  assert(my->drv);
  assert(my->drv->inst);
  
  is_beat = my->drv->is_beat(my->drv->inst, samples, len, thr);

  if (is_beat)
    inst->out_b->number = 1.0;
  else
    inst->out_b->number = 0;

}

//----------------------------------------------------------------------------
