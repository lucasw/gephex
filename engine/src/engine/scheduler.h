#ifndef INCLUDED_SCHEDULER_H
#define INCLUDED_SCHEDULER_H

#include <stdexcept>
#include <list>

#include "utils/autoptr.h"

class ITask;

namespace engine
{

  /**
   * Nicht Präemptiver Scheduler. Er ruft ITask Objekte in bestimmten 
   * Intervallen auf. Bein Hinzufuegen einer Task kann das Intervall
   * festgelegt werden, in dem diese Task aufgerufen werden soll.
   * Der Scheduler kann aber nicht garantieren dass eine Task immer
   * pünktlich aufgerufen wird, da das auch davon abhängt ob sich die
   * anderen Tasks "fair" verhalten.
   * Eine Task wird solange immer wieder aufgerufen bis ihre run() Methode
   * einmal false zurückliefert.
   */
  class IScheduler
  {
  public:
  
    /**
     * Fügt eine neue Task hinzu. Die Task wird (wenn alles klappt)
     * im Intervall timeInMillis ms periodisch aufgerufen.
     * @param task Die Task die zur periodischen Ausführung bestimmt ist.
     * @param timeInMillis Das Intervall in dem die Ausführung der
     *        task angestossen wird.
     */
    virtual void addTask(ITask& task,int timeInMillis) = 0;

    /**
     * Fügt eine Leerlauf Task hinzu. Die Task wird immer dann
     * aufgerufen, wenn keine andere Task zur Ausführung ansteht.
     * Es kann also passieren dass sie nie aufgerufen wird.
     * @param task Die Task die als Leerlauftask dienen soll.
     * @param maxSleepInMillis Die maximale Zeit für die die Leerlauftask
     *        ausgesetzt werden darf. Wenn ein Wert > 0 angegeben wird
     *        kann es sein dass task nicht aufgerufen wird, obwohl keine
     *        andere Task ansteht (zur Reduzierung der CPU-Last).
     */
    //virtual void setIdleTask(ITask& task,int maxSleepInMillis) = 0;

    /**
     * Startet die Ausführung der Tasks. Kehrt erst zurück, wenn alle
     * Tasks beendet sind (d.h. bis alle false zurückgeben), oder wenn
     * stop() aufgerufen wird.
     */
    virtual void run() = 0;

    /**
     * Entfernt eine bestimmte Task wieder.
     * @param task Die Task die entfernt werden soll.
     */
    virtual void killTask(ITask& task) = 0;

    /**
     * Aendert das Intervall in dem eine Task aufgerufen wird.
     * @param task Die task deren Zeit geaendert werden soll.
     * @param newTimeInMillis Die neue Intervallzeit in ms.
     */
    virtual void changeTaskTime(ITask& task,int newTimeInMillis) = 0;

    /**
     * Stoppt den Scheduler.
     */
    virtual void stop() = 0;
  };

  struct TaskControlBlock;

  class Scheduler : public IScheduler
  {
  public:
    Scheduler();
    virtual ~Scheduler();

    virtual void addTask(ITask& task,int timeInMillis);

    //virtual void setIdleTask(ITask& task,int maxSleepInMillis);

    virtual void run();

    virtual void killTask(ITask& task) throw (std::runtime_error);

    virtual void changeTaskTime(ITask& task,int newTimeInMillis)
      throw (std::runtime_error);

    virtual void stop();
  private:
    typedef utils::AutoPtr<TaskControlBlock> TaskControlBlockPtr;
    typedef std::list<TaskControlBlockPtr> TaskList;
    TaskList tasks;

    volatile bool m_stopped;
  };

} // end of namespace engine

#endif

