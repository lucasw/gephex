#ifndef INCLUDED_IMUTEX_H
#define INCLUDED_IMUTEX_H

//-----------------------------------------------------------------------------

namespace thread
{

//TODO: Exceptions (see the Implementation)
class IMutex
{
  IMutex(const IMutex&); // not implemented;
  IMutex& operator=(const IMutex&); // not implemented;
public:
  IMutex();
  virtual ~IMutex();

  virtual void lock() = 0;
  virtual void unlock() = 0;
};

} // end of namespace

//-----------------------------------------------------------------------------

#endif

