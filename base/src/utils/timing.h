#ifndef INCLUDED_TIMING_H
#define INCLUDED_TIMING_H

namespace utils {

  /**
   * This class provides basic timing functionality.
   */
  class Timing
  {
  public:
    /**
     * Returns the current system time in ms.
     * @return the system time in millis.
     */
    static unsigned long getTimeInMillis();

    /**
     * Suspends the process for a given amount of time.
     * Depending on the OS, the resolution may be higher
     * than on ms (f.e on Linux/i368, the suspend time
     * is at least 10ms).
     * @param millis the time to suspend in ms
     */
    static void sleep(unsigned long millis);
  };

}

#endif
