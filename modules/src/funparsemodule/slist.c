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

#include "slist.h"

#include <stdlib.h>

typedef slist_iterator_t slist_node_t;

struct slist_iterator_s_t
{
  void* value;
  slist_node_t next;
};

struct slist_s_t
{
  slist_node_t head;
  int size;
};


slist_node_t slist_node_create(void* value, slist_node_t next)
{
  slist_node_t node = (slist_node_t) malloc(sizeof(*node));
  node->value = value;
  node->next  = next;

  return node;
}

void slist_node_free(slist_node_t n)
{
  free(n);
}

slist_t slist_create()
{
  slist_t slist = (slist_t) malloc(sizeof(*slist));
  slist->head = 0;
  slist->size = 0;

  return slist;
}

void slist_free(slist_t slist)
{
  slist_node_t n = slist_begin(slist);
  slist_node_t nn;
  while (n != slist_end(slist))
    {
      nn = n->next;
      slist_node_free(n);
      n = nn;
    }
}

int slist_size(const slist_t slist)
{
  return slist->size;
}

void slist_push_front(slist_t slist, void* value)
{
  slist_node_t n = slist_node_create(value, slist->head);

  slist->head = n;
  slist->size += 1;
}

slist_iterator_t slist_begin(slist_t slist)
{
  return slist->head;
}

slist_iterator_t slist_end(slist_t slist)
{
  return 0;
}

void slist_iter_advance(slist_iterator_t* it)
{
  *it = (*it)->next;
}

void* slist_iter_deref(slist_iterator_t it)
{
  return it->value;
}

slist_iterator_t slist_find_if(slist_t slist, pred_t pred, void* closure)
{
  slist_iterator_t it = slist_begin(slist);
  while( it != slist_end(slist) )
    {
      void* v = slist_iter_deref(it);
      if ( pred(v, closure) )
        return it;

      slist_iter_advance(&it);
    }

  return slist_end(slist);
}
