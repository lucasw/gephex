#ifndef INCLUDED_KEYBOARDMANAGER_H
#define INCLUDED_KEYBOARDMANAGER_H

#include "utils/autoptr.h"

namespace gui {

  class IKeyListener;
  class Key;
  class KeyGrabberImpl;

  /**
   * This class does the global keyboard managment.
   */
class KeyboardManager
{
public:

  KeyboardManager();
  ~KeyboardManager();

  void turnOn();
  void turnOff();
  
  void registerListener(IKeyListener& listener,
				const Key& key);

  void removeListener(IKeyListener& listener);

private:
  utils::AutoPtr<KeyGrabberImpl> m_impl;
};

}

#endif
