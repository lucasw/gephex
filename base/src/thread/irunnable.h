#ifndef INCLUDED_IRUNNABLE_H
#define INCLUDED_IRUNNABLE_H

//-----------------------------------------------------------------------------

namespace thread
{

class IRunnable
{
public:
  virtual void run() = 0;
};

} // end of namespace

//-----------------------------------------------------------------------------

#endif
