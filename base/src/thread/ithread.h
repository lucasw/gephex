#ifndef INCLUDED_ITHREAD_H
#define INCLUDED_ITHREAD_H

namespace thread
{

class IRunnable;

//-----------------------------------------------------------------------------

// A simple thread class. After construction, a new thread has been created 
// thats not yet running. 
// After start() is invoked the run() method of the runner is started
// in this new thread. The thread exits when run() returns.
class IThread 
{
private:

  IThread(const IThread &); //not implemented
  IThread & operator=(const IThread &); //not implemented

protected:
  volatile bool _isRunning;
  IRunnable& m_runner;

public:
  // create a new (stopped) thread
  IThread(IRunnable& runner);
  virtual ~IThread();

  // start the thread (the run() method is called)
  // dont override!
  void start();

  // true, while the thread executes the run() method
  // false before and afterwards
  // dont override!
  bool isRunning() const;

  // let the current thread sleep for millis ms.
  //virtual void sleep(int millis) = 0;

  // tell the scheduler to continue with another thread
  //virtual void yield() = 0;
};

//-----------------------------------------------------------------------------

} // end of namespace
#endif
