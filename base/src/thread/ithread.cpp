#include "ithread.h"

namespace thread
{

//-----------------------------------------------------------------------------

IThread::IThread(IRunnable& runner)
  : _isRunning(false), m_runner(runner)
{
}

IThread::~IThread() {
}

void IThread::start() {
  _isRunning = true;
}

bool IThread::isRunning() const { 
  return _isRunning; 
}

} // end of namespace

//-----------------------------------------------------------------------------
