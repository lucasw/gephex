#include "x11stuff.h"

int x11_win_on_top(Bool on_top,
                    Display* dpy,
                    Window win)
{
  /*  if (on_top)
    {
      XUnmapWindow( dpy, win );
      XSetTransientForHint(dpy, win,
                           RootWindow(dpy,
                                      DefaultScreen(dpy)));

      XMapRaised( dpy, win );
      XRaiseWindow( dpy, win );
      XFlush(dpy);
      //TODO: error handling
      }*/
  /*  else
    {
    }*/
  return 1;
}


int x11_win_frame(Bool frame,
                   Display* dpy,
                   Window win)
{
  XSetWindowAttributes attr;
  XWindowAttributes attribs;
  int x, y;

  
  XGetWindowAttributes(dpy, win, &attribs);
  x = attribs.x;
  y = attribs.y;

  XUnmapWindow( dpy, win );
  XFlush(dpy);

  attr.override_redirect = ((frame == False) ? True : False);
  //  printf("override_redirect = %i\n", attr.override_redirect);

  XChangeWindowAttributes(dpy, win,
                          CWOverrideRedirect, &attr);

  if (!frame)
    {
      x = y = 0;
    }

  {
    XWindowChanges chg;
    chg.x = x;
    chg.y = y;
    XConfigureWindow(dpy, win, CWX | CWY, &chg);
  }

  XMapWindow( dpy, win );

  XFlush(dpy);
  //TODO: error handling
  return 1;
}

