#ifndef INCLUDED_BLOCK_H
#define INCLUDED_BLOCK_H

#include <cstdlib>
#include <iostream>

#include "config.h"


inline unsigned char* createRandomBlock(int len)
{
  unsigned char* data = new unsigned char[len];
  for (int i = 0; i < len; ++i)
#ifdef OS_POSIX
	data[i] = (char) (((double) random() / RAND_MAX) * 255.);
#endif
#ifdef OS_WIN32
    data[i] = (char) (((double) rand() / RAND_MAX) * 255.);
#endif
  return data;
}

inline bool compareBlocks(const unsigned char* d1, int l1,
			  const unsigned char* d2, int l2)
{
  if (l1 != l2)
    return false;

  for (int i = 0; i < l1; ++i)
    {
      if (d1[i] != d2[i])
	return false;
    }

  return true;
}

inline void printBlock(std::ostream& s,const unsigned  char* d, int l)
{
  s << l << '[';
  for (int i = 0; i < l; ++i)
    {
      s << (int) d[i];
      if (i != l-1)
	s << ',';
    }
  s << ']';
}
#endif
