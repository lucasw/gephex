#ifndef INCLUDED_ITASK_H
#define INCLUDED_ITASK_H

/**
 * Interfaces for non-preemptive tasks.
 */
class ITask
{
public:
  /**
   * This method gives control to the task. It is expected, that
   * the task gives back control (by returning) soon.
   * @return true if everything went fin, false if the task doesnt
   *         want to be called again
   */
	virtual bool run() = 0;
};

#endif

