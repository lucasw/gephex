#ifndef INCLUDED_ITHREAD_UTIL_H
#define INCLUDED_ITHREAD_UTIL_H

//-----------------------------------------------------------------------------

namespace thread
{

class IThreadUtil
{
 public:
  virtual void sleep(unsigned long microsecs) = 0;
};

} // end of namespace

//-----------------------------------------------------------------------------

#endif

