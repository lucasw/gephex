#ifndef INCLUDED_ITASK_H
#define INCLUDED_ITASK_H

/**
 * simple interface for non-preemptive tasks.
 */
class ITask
{
 public:

  /**
   * This method executes one slice of the task. The run method must return
   * control as soon as possible(non-preemptive).
   *
   * \returns the thread finished status. 
   *          It is true if there are task slices left to be executed and 
   *          false if the scheduler mustn't call the run method again.
   */
  virtual bool run() = 0;
};

#endif

