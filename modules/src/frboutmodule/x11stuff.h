#ifndef INCLUDED_X11_STUFF_H
#define INCLUDED_X11_STUFF_H

#include <X11/Xlib.h>

/**
 * X11 helper functions.
 */

/**
 * Moves a window to top / from top.
 * \param on_top if True, the window is moved on top
 *               if False, the window is no longer on top
 * \param dpy the display of the window
 * \param win the window
 * \return 0 on error
 */
int x11_win_on_top(Bool on_top,
                   Display* dpy,
                   Window win);

/**
 * Removes/adds a frame (+ window decoration).
 * \param on_top if True, the decoration is removed
 *               if False, the window decoration is restored
 * \param dpy the display of the window
 * \param win the window
 * \return 0 on error
 */
int x11_win_frame(Bool frame,
                   Display* dpy,
                   Window win);
#endif
