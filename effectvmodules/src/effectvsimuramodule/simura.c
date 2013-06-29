/*
 * EffecTV - Realtime Digital Video Effector
 * Copyright (C) 2001-2003 FUKUCHI Kentaro
 *
 * SimuraTV - color distortion and mirrored image effector
 * Copyright (C) 2001-2002 FUKUCHI Kentaro
 *
 */

#include <stdlib.h>
#include <string.h>
#include "EffecTV.h"
#include "utils.h"

static int start(void);
static int stop(void);
static int draw(RGB32 *src, RGB32 *dest);
//static int event();

static char *effectname = "SimuraTV";
static int stat;
static RGB32 color = 0x000000;
static int mirror = 1;
static int width;
static int hwidth;
static int height;
static int hheight;
static RGB32 colortable[26] = {
	0x000080, 0x0000e0, 0x0000ff,
	0x008000, 0x00e000, 0x00ff00,
	0x008080, 0x00e0e0, 0x00ffff,
	0x800000, 0xe00000, 0xff0000,
	0x800080, 0xe000e0, 0xff00ff,
	0x808000, 0xe0e000, 0xffff00,
	0x808080, 0xe0e0e0, 0xffffff,
	0x76ca0a, 0x3cafaa, 0x60a848, 0x504858, 0x89ba43
};

static void mirror_no(RGB32 *, RGB32 *);
static void mirror_u(RGB32 *, RGB32 *);
static void mirror_d(RGB32 *, RGB32 *);
static void mirror_r(RGB32 *, RGB32 *);
static void mirror_l(RGB32 *, RGB32 *);
static void mirror_ul(RGB32 *, RGB32 *);
static void mirror_ur(RGB32 *, RGB32 *);
static void mirror_dl(RGB32 *, RGB32 *);
static void mirror_dr(RGB32 *, RGB32 *);

effect *simuraRegister()
{
	effect *entry;
	int i;
	RGB32 tmp[26];
	
/* 	for(i=0; i<26; i++) { */
/* 		tmp[keytable[i] - 'a'] = colortable[i]; */
/* 	} */
/* 	for(i=0; i<26; i++) { */
/* 		colortable[i] = tmp[i]; */
/* 	} */

	width = video_width;
	height = video_height;
	hwidth = video_width/2;
	hheight = video_height/2;

	entry = (effect *)malloc(sizeof(effect));
	if(entry == NULL) {
		return NULL;
	}
	
	entry->name = effectname;
	entry->start = start;
	entry->stop = stop;
	entry->draw = draw;
	entry->event = 0;//event;

	return entry;
}

static int start()
{
	stat = 1;
	return 0;
}

static int stop()
{
	stat = 0;
	return 0;
}

static int draw(RGB32 *src, RGB32 *dest)
{
	switch(mirror) {
	case 1:
		mirror_l(src, dest);
		break;
	case 2:
		mirror_r(src, dest);
		break;
	case 3:
		mirror_d(src, dest);
		break;
	case 4:
		mirror_dl(src, dest);
		break;
	case 5:
		mirror_dr(src, dest);
		break;
	case 6:
		mirror_u(src, dest);
		break;
	case 7:
		mirror_ul(src, dest);
		break;
	case 8:
		mirror_ur(src, dest);
		break;
	case 0:
	default:
		mirror_no(src, dest);
		break;
	}

	return 0;
}



static void mirror_no(RGB32 *src, RGB32 *dest)
{
	int i;

	for(i=0; i<video_area; i++) {
		dest[i] = src[i] ^ color;
	}
}

static void mirror_u(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=0; y<hheight; y++) {
		for(x=0; x<width; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_d(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=hheight; y<height; y++) {
		for(x=0; x<width; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_l(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=0; y<height; y++) {
		for(x=0; x<hwidth; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_r(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=0; y<height; y++) {
		for(x=hwidth; x<width; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_ul(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=0; y<hheight; y++) {
		for(x=0; x<hwidth; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_ur(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=0; y<hheight; y++) {
		for(x=hwidth; x<width; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_dl(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=hheight; y<height; y++) {
		for(x=0; x<hwidth; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

static void mirror_dr(RGB32 *src, RGB32 *dest)
{
	int x, y;

	for(y=hheight; y<height; y++) {
		for(x=hwidth; x<width; x++) {
			dest[y*width+x] = src[y*width+x] ^ color;
			dest[y*width+(width-x-1)] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+x] = src[y*width+x] ^ color;
			dest[(height-y-1)*width+(width-x-1)] = src[y*width+x] ^ color;
		}
	}
}

