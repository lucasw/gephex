#ifndef INCLUDED_LIBEFFECTTV_H
#define INCLUDED_LIBEFFECTTV_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

/**
 *
 * Simple emulation library, that helps to run EffecTV-effects
 * in GePhex.
 *
 */

/*****************************************************************************/

/**
 * Interface of the emulation library
 */

typedef void (*effectv_lock_funcT)(void);
typedef void (*effectv_unlock_funcT)(void);

struct effectv_Effect;

/**
 * Takes a pointer to a EffecTV register function
 */
struct effectv_Effect* effectv_init(void* register_func,
                                    effectv_lock_funcT lock_func,
                                    effectv_unlock_funcT unlock_func);

int effectv_draw(struct effectv_Effect* effect,
                  unsigned char* vid, unsigned char* screen,
		  int xsize, int ysize);


void effectv_teardown(struct effectv_Effect* effect);

/*****************************************************************************/

/**
 * Necessary global vars and functions for the EffecTV effects
 */
extern int video_width;
extern int video_height;
extern int video_area;
extern int screen_width;
extern int screen_height;
extern int screen_scale;
extern int stretch;

unsigned char* video_getaddress();
unsigned char* screen_getaddress();

#if defined(OS_WIN32)
void bzero(void* ptr, int size);
#endif
/*****************************************************************************/

#endif

