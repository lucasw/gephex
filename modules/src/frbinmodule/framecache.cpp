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

#include "framecache.h"

#include <algorithm>
#include <vector>
#include <list>
#include <cassert>

#include <iostream>

//-----------------------------------------------------------------------------

class Cache;


//----------------------------------------------------------------------------

bool compare_tag(const std::pair<int, uint_32*>& lhs,
                 const std::pair<int, uint_32*>& rhs)
{
  return lhs.first < rhs.first;
}

class Cache
{
public:
  Cache() {};
	
  uint_32* lookup(int pos) const
  {
    FrameVector::const_iterator 
      it = std::lower_bound(m_frames.begin(),
                            m_frames.end(),
                            std::make_pair(pos,(uint_32*) 0),
                            compare_tag);

    if (it != m_frames.end() && it->first == pos)
      return it->second;
    else
      return 0;
  }

  void store(int pos, uint_32* frb)
  {
    FrameVector::iterator 
      it = std::upper_bound(m_frames.begin(),
                            m_frames.end(),
                            std::make_pair(pos, (uint_32*) 0),
                            compare_tag);
		
    if (it != m_frames.end() && it->first == pos)
      {
        delete[] it->second;
        it->second = frb;
      }
    else
      {
        m_frames.insert(it, std::make_pair(pos, frb));
      }
  }

  // removes up to num_frames frames
  // returns number of frames actually deleted
  int remove(int num_frames)
  {
    if (m_frames.empty())
      return 0;
    std::pair<int, uint_32*> p = m_frames.front();
    m_frames.erase(m_frames.begin());
    delete[] p.second;
    return 1;
  }

  bool empty() const
  {
    return m_frames.empty();
  }
	
  ~Cache()
  {
    for (FrameVector::iterator it = m_frames.begin();
         it != m_frames.end(); ++it)
      {
        delete[] it->second;
      }
  }
	
private:
  typedef std::vector<std::pair<int,uint_32*> > FrameVector;
  FrameVector m_frames;
	
};

//------------------------------------------------------------------------

struct CacheKey
{
  CacheKey(const std::string fn, int w, int h)
    : file_name(fn), width(w), height(h), c(0), time_stamp(0){}

  ~CacheKey()
  {		
  }
	
  bool operator==(const CacheKey& rhs) const 
  {
    return file_name == rhs.file_name &&
      width == rhs.width && height == rhs.height;
  }

  bool empty() const
  {
    return c->empty();
  }
		
  std::string file_name;
  int width;
  int height;
  Cache* c;
  int time_stamp;
};

//-----------------------------------------------------------------

class FrameCache::Impl
{
public:
  Impl(int size_in_mbytes)
    : m_max_size(size_in_mbytes*1024*1024), m_size(0), m_time(0)
  {
  }
	
  ~Impl()
  {
    flush();
  }
	
  void store(const std::string& file_name, int frame_number,
             int width, int height, uint_32* framebuffer)
  {
    CacheKey key(file_name, width, height);
    CacheList::iterator it = std::find(m_cache.begin(), m_cache.end(), key);

    // watch size + replacement strategy
    int size = width*height*4;

    if (m_size + size > m_max_size)
      {
        // find a cache with minimal timestamp and remove one image
        CacheList::const_iterator min_it = m_cache.end();
        int min_time = m_time+1;
        for (CacheList::const_iterator it = m_cache.begin();
             it != m_cache.end(); ++it)
          {
            if (!it->empty() && it->time_stamp < min_time)
              {
                min_it = it;
                min_time = it->time_stamp;
              }
          }
        if (min_it != m_cache.end())
          {			
            int size_per_frame = min_it->width*min_it->height*4;
            int num_frames 
              = (int) (((double)((m_size + size) - m_max_size)) / size_per_frame +0.5);
            int removed = min_it->c->remove(num_frames);
            m_size -= size_per_frame * removed;				
          }
      }

    if (it == m_cache.end())
      {					
        key.c = new Cache();
        key.time_stamp = m_time;
        m_cache.push_back(key);
        key.c->store(frame_number, framebuffer);			
      }
    else
      {	
        it->time_stamp = m_time;
        it->c->store(frame_number, framebuffer);
      }

    m_size += size;
    ++m_time;
  }
	
	
  uint_32* lookup(const std::string& file_name, int frame_number,
                  int width, int height)
  {
    CacheList::iterator it = std::find(m_cache.begin(), 
                                       m_cache.end(),
                                       CacheKey(file_name, width, height));
    if (it == m_cache.end())
      return 0;
    else
      {
        it->time_stamp = m_time;
        return it->c->lookup(frame_number);
      }
    ++m_time;
  }
	
	
  void flush()
  {		
    for (CacheList::const_iterator it = m_cache.begin();
         it != m_cache.end(); ++it)
      {
        delete it->c;
      }
    m_cache.clear();
    m_time = 0;
    m_size = 0;
  }
	
private:
  int m_max_size;
  int m_size;
  int m_time;
  typedef std::list<CacheKey> CacheList;
  CacheList m_cache;
};


//------------------------------------------------------------------------

FrameCache::FrameCache(int size_in_mbytes)
  : m_impl(new Impl(size_in_mbytes))
{
}

FrameCache::~FrameCache()
{  
}

void FrameCache::store(const std::string& file_name, int frame_number,
                       int width, int height, uint_32* framebuffer)
{
  m_impl->store(file_name, frame_number, width, height, framebuffer);
}


uint_32* FrameCache::lookup(const std::string& file_name, int frame_number,
                            int width, int height) const
{
  return m_impl->lookup(file_name, frame_number, width, height);
}


void FrameCache::flush()
{
  m_impl->flush();
}

//------------------------------------------------------------------------
