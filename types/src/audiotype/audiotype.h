#ifndef INCLUDED_AUDIO_TYPE_H
#define INCLUDED_AUDIO_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "basic_types.h"

/**
 * PCM raw audio data. 
 *  len: Number of used bytes of the buffer
 *  capacity: Maximum length of the buffer
 *  channels: 1 -> mono, 2 -> stereo
 *  sample_rate: in hertz, valid values are for example 8000, 11025,
 *               22050, 44100
 *  samples: block of capacity doubles, each representing one sample.
 *    The first len doubles contain the audio data.
 *    Every sample is one double value between -1 and 1. If channels equals 2,
 *    the order of the samples is: first_left, first_right, second_left,
 *    second_right, ...
 *
 */
typedef struct AudioType_
{
  int len;
  int capacity;
  int channels;
  int sample_rate;
  double* samples;
} AudioType;

static __inline void audio_initInstance(AudioType* newType)
{
  newType->len         = 0;
  newType->capacity    = 0;
  newType->samples     = 0;
  newType->channels    = 1;
  newType->sample_rate = 44100;
}

static __inline AudioType* audio_newInstance(void)
{
  AudioType* newType = (AudioType*) malloc(sizeof(AudioType));
  audio_initInstance(newType);
  return newType;
}

static __inline void audio_resize(AudioType* dst, int new_size)
{
  double* new_samples;

  if (new_size < dst->len)
    return;

  new_samples = (double*) malloc(new_size * sizeof(double));
  
  if (dst->samples != 0) {
    memcpy(new_samples, dst->samples, dst->len * sizeof(double));
    free(dst->samples);
  }

  dst->capacity = new_size;
  dst->samples     = new_samples;
}

static __inline void audio_set_buffer(AudioType* dst, double* buf,
                                      int len)
{
  if (len == 0)
    return;

  if (dst->capacity < len)
    audio_resize(dst, len);

  assert(dst->capacity >= len);
  assert(dst->samples != 0);

  memcpy(dst->samples, buf, len * sizeof(double));
  dst->len = len;
}

static __inline void audio_assign(AudioType* dst, const AudioType* src)
{
  if (src->len == 0)
    return;

  if (dst->capacity < src->len)
    audio_resize(dst, src->len);
  
  assert(dst->capacity >= src->len);
  assert(dst->samples != 0);

  memcpy(dst->samples, src->samples, src->len * sizeof(double));
  dst->len = src->len;
}

static __inline void audio_deleteInstance(AudioType* dst)
{
  if (dst->samples != 0)
    free(dst->samples);

  free(dst);
}

static __inline int audio_serialize(const AudioType* pos,
                                    char* buffer, int bufferLen)
{
  return 0;
}

static __inline void audio_deSerialize(const char* buffer,int len,
                                       AudioType* pos)
{
}

#endif
