#ifndef INCLUDED_OUTPUT_DRIVER_H
#define INCLUDED_OUTPUT_DRIVER_H

/**
 * Interface for outputdrivers used by the X11-outputmodule.
 */

struct DriverInstance;

struct OutputDriver {
  struct DriverInstance* inst;

  /**
   * The caller must destroy the driver returned with destroy.
   *
   * If an error occurs, 0 is returned and error_text is set.
   */
  struct DriverInstance* (*new_instance)(const char* server_name,
                                         int width, int height,
                                         char* error_txt, int buflen);

  void (*destroy)(struct DriverInstance* self);

  int  (*resize)(struct DriverInstance* self, int width, int height);

  /**
   * The driver is responsible for scaling, if (width, height) is not equal
   * to the drivers current resolution (either set by init or resize).
   *
   * This is done to allow the use of hw-scalers.
   */
  int  (*blit)(struct DriverInstance* self,
               const unsigned char* fb,
               int width, int height,
               char* error_text, int buflen);

};

#endif
