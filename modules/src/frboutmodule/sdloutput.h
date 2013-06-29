/* SDL Output driver
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

#ifndef INCLUDED_SDL_OUTPUT_H
#define INCLUDED_SDL_OUTPUT_H

struct OutputDriver;

/*int SDL_init(char* error_text, int text_len);

int SDL_shutdown(char* error_text, int text_len);*/

/**
 * The returned Driver must be freed by the caller!
 */
struct OutputDriver* SDL_get_driver();

#endif
