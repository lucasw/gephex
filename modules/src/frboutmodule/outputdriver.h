/* Interface for output drivers
  Copyright (C) 2003 Georg Seidel
  This file is part of GePhex.

  GePhex is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  GePhex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
    
  You should have received a copy of the GNU General Public
  License along with GePhex; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA.  
      
  You can reach me via email: georg.seidel@web.de
*/

#ifndef INCLUDED_OUTPUT_DRIVER_H
#define INCLUDED_OUTPUT_DRIVER_H


struct blit_params
{
  int    mirrorx;
  int    mirrory;
  double brightness;
  double contrast;
  double gamma;
  int    invert;
};

struct DriverInstance;

/**
 * Interface for outputdrivers used by the frb-outputmodule.
 */
struct OutputDriver {
  struct DriverInstance* inst;

  /**
   * The caller must destroy the driver returned with destroy.
   *
   * If an error occurs, 0 is returned and error_text is set.
   */
  struct DriverInstance* (*new_instance)(const char* server_name,
                                         int xpos, int ypos,
                                         int width, int height,
                                         int mmx_supported,
                                         char* error_txt, int buflen);

  void (*destroy)(struct DriverInstance* self);

  /**
   * Note that resize can be called more often than needed.
   * The driver should check if a resize is necessary
   * and only perform one in that case.
   */
  int  (*resize)(struct DriverInstance* self, int width, int height,
                 char* error_text, int text_len);

  /**
   * The driver is responsible for scaling, if (width, height) is not equal
   * to the drivers current resolution (either set by init or resize).
   *
   * This is done to allow the use of hw-scalers.
   */
  int  (*blit)(struct DriverInstance* self,
               const unsigned char* fb,
               int width, int height,
               struct blit_params* params,
               char* error_text, int buflen);


  // The following functions are optional. They can be set to 0 by the driver
  // to indicate missing support.

  /**
   * Returns the window position in *xpos, *ypos
   */
  int (*window_pos)(struct DriverInstance* self, int* xpos, int* ypos,
                    char* error_text, int text_len);

  /**
   * Shows/hides the window frame (including titlebar)
   */
  int (*frame)(struct DriverInstance* self, int frame_visible,
               char* error_text, int text_len);

  /**
   * Sets the output window to "always on top"
   */
  int (*always_on_top)(struct DriverInstance* self, int on_top,
                       char* error_text, int text_len);

  /**
   * Moves the output window to a specific monitor.
   */
  int (*to_monitor)(struct DriverInstance* self, int monitor,
                    char* error_text, int text_len);


};

#endif
