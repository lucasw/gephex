#include "tagdispatcher.h"

#include "idatalistener.h"

#include <sstream>

namespace net {

  template <typename Tag>
  TagDispatcher<Tag>::TagDispatcher() {}

  template <typename Tag>
  TagDispatcher<Tag>::~TagDispatcher() {}

  template <typename Tag>
  void TagDispatcher<Tag>::registerListener(const Tag& t,
					    IDataListener& listener)
  {
    m_listeners.insert(std::make_pair(t, &listener));
  }

  template <typename Tag>
  void TagDispatcher<Tag>::dataReceived(const Tag& tag, const utils::Buffer& b)
  {
    typename ListenerMap::const_iterator it = m_listeners.find(tag);
    if (it == m_listeners.end())
      {
	std::ostringstream os;
	os << "No listener found for Tag = `" << tag << "`"
	   << std::endl;

	throw std::runtime_error(os.str().c_str());
      }
    else
      {
	IDataListener* listener = it->second;
	listener->dataReceived(b);
      }
  }
}
