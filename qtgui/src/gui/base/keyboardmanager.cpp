#include "keyboardmanager.h"

#include <list>
#include <map>

#include <qwidget.h>

#include "ikeylistener.h"
#include "key.h"

namespace gui {

  // < operation for keys
  struct ltkey
  {
    bool operator()(const Key& lhs, const Key& rhs) const
    {
      return (lhs.code() < rhs.code() ||
	      (lhs.code() == rhs.code() &&
	       lhs.modifierMask() < rhs.modifierMask()));
    }
  };

  class KeyGrabberImpl : public QWidget
  {
  public:
    KeyGrabberImpl() : QWidget(0, "keyGrabber") { }

    ~KeyGrabberImpl() {};

    void turnOn()
    {
      grabKeyboard();
    }

    void turnOff()
    {
      releaseKeyboard();
    }
  
    void registerListener(IKeyListener& listener,
			  const gui::Key& key)
    {
      m_listeners[key].push_back(&listener);
    }

  void removeListener(IKeyListener& listener)
  {
    std::list<gui::Key> emptyList;

    for (ListenerMap::iterator it = m_listeners.begin();
	 it != m_listeners.end(); ++it)
      {
	ListenerList& l = it->second;	
	l.remove(&listener);
	if (l.empty())
	  {
	    emptyList.push_back(it->first);
	  }
      }

    for (std::list<gui::Key>::iterator it2 = emptyList.begin();
	 it2 != emptyList.end(); ++it2)
      {
	m_listeners.erase(*it2);
      }
  }

  protected:
    void keyPressEvent ( QKeyEvent * e )
    {
      gui::Key k = buildKeyFromKeyEvent(*e);

      //      std::cout << "Key has been pressed: " << k.code() << ","
      //		<< k.modifierMask() << std::endl;

      ListenerMap::const_iterator it = m_listeners.find(k);

      if (it == m_listeners.end())
	{
	  //	  std::cout << "no listener found" << std::endl;
	  e->ignore();
	  return;
	}

      const ListenerList& l = it->second;

      assert(!l.empty());

      for (ListenerList::const_iterator it2 = l.begin();
	   it2 != l.end(); ++it2)
	{
	  (*it2)->keyPressed(k);
	}	   
    }

    void keyReleaseEvent ( QKeyEvent * e )
    {
      gui::Key k = buildKeyFromKeyEvent(*e);

      ListenerMap::const_iterator it = m_listeners.find(k);

      if (it == m_listeners.end())
	{
	  e->ignore();
	  return;
	}

      const ListenerList& l = it->second;

      assert(!l.empty());

      for (ListenerList::const_iterator it2 = l.begin();
	   it2 != l.end(); ++it2)
	{
	  (*it2)->keyReleased(k);
	}
    }

  private:
    gui::Key buildKeyFromKeyEvent(const QKeyEvent& e)
    {
      //TODO: this assumes, that the constants in qnamespace.h and key.h
      // are exactly the same
      int state = e.state();
      int modifierMask = 0;

      //      std::cout << "State is "  << state << std::endl;

      if (state & ShiftButton)
	modifierMask |= gui::Key::ShiftModifier;

      if (state & AltButton)
	modifierMask |= gui::Key::AltModifier;

      if (state & ControlButton)
	modifierMask |= gui::Key::CtrlModifier;

      return gui::Key(e.key(), modifierMask);
    }

  private:
    typedef std::list<IKeyListener*> ListenerList;
    typedef std::map<gui::Key, ListenerList, ltkey> ListenerMap;
    ListenerMap m_listeners;
  };
  
  KeyboardManager::KeyboardManager()
    : m_impl(new KeyGrabberImpl())
  {
  }

  KeyboardManager::~KeyboardManager()
  {
  }

  void KeyboardManager::turnOn()
  {
    m_impl->turnOn();
  }

  void KeyboardManager::turnOff()
  {
    m_impl->turnOff();
  }
  
  void KeyboardManager::registerListener(IKeyListener& listener,
					 const Key& key)
  {
    //    std::cout << "Listener has been registered: " << key.code() << ","
    //	      << key.modifierMask() << std::endl;
    m_impl->registerListener(listener, key);
  }

  void KeyboardManager::removeListener(IKeyListener& listener)
  {
    m_impl->removeListener(listener);
  }
}
