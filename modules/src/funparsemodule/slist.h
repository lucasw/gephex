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

#ifndef INCLUDED_SLIST_H
#define INCLUDED_SLIST_H

struct slist_s_t;
typedef struct slist_s_t* slist_t;

struct slist_iterator_s_t;
typedef struct slist_iterator_s_t* slist_iterator_t;

slist_t slist_create();
void slist_free(slist_t);

int slist_size(const slist_t slist);

void slist_push_front(slist_t, void* value);

slist_iterator_t slist_begin(slist_t);
slist_iterator_t slist_end(slist_t);
void slist_iter_advance(slist_iterator_t*);
void* slist_iter_deref(slist_iterator_t);

typedef int (*pred_t)(void* item, void* closure);
slist_iterator_t slist_find_if(slist_t slist, pred_t pred, void* closure);


#endif
