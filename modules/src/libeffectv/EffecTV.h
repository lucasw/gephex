/*
 *
 * This is a slightly modified compatibility header, to make EffecTV
 * effects work with GePhex.
 * Taken from EffecTV version 0.3.8
 *
 * Changes made:
 *  -removed includes to other headers
 *  -removed macros and SDL-dependencies
 */

/*
 * EffecTV - Realtime Digital Video Effector
 * Copyright (C) 2001-2002 FUKUCHI Kentaro
 *
 * EffecTV.h: common header
 *
 */

#ifndef __EFFECTV_H__
#define __EFFECTV_H__

typedef unsigned int RGB32;

#define PIXEL_SIZE (sizeof(RGB32))

typedef struct _effect
{
  char *name;
  int (*start)(void);
  int (*stop)(void);
  int (*draw)(void);
  int (*event)(void *);
} effect;

typedef effect *effectRegistFunc(void);

extern int debug;

#endif /* __EFFECTV_H__ */
