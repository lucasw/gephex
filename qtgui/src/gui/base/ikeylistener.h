#ifndef INCLUDED_IKEY_LISTENER_H
#define INCLUDED_IKEY_LISTENER_H

namespace gui {

  class Key;

  class IKeyListener
  {
  public:
    virtual void keyPressed(const Key& key) = 0;
    virtual void keyReleased(const Key& key) = 0;
  };
}

#endif
