#include "sequence.h"
#include "interfaces/isequenceupdatereceiver.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include <algorithm>
#include <ctime>
#include <cassert>

namespace
{
 int clock2Ms(int clock)
  {
    return static_cast<int>((1000. * clock) 
			    / static_cast<double>(CLOCKS_PER_SEC));

  } 
}
	
namespace sequencer
{
  class ActionPairCompare
  {
  public:
    bool operator()(const std::pair<int, utils::AutoPtr<Action> >& p1,
		    const std::pair<int, utils::AutoPtr<Action> >& p2)
    {
      return p1.second->time() < p2.second->time();
    }
  };
	
  /*----------------------Scene-----------------------------------------*/
	
  /*Scene::Scene(): _length(-1), _name(0)
    {}*/
	
  Action::Action(const std::string& command, int time)
    : m_command(command), m_time(time)
  {}
	
  std::string Action::command() const
  {
    return m_command;
  }
	
  int Action::time() const
  {
    return m_time;
  }
	
  void Action::setTime(int time)
  {
    m_time = time;
  }

  /*----------------------Action done-----------------------------------*/

  /*----------------------Sequence-------------------------------------------*/

  Sequence::Sequence(const std::string& id, const std::string& name)
    : m_id(id), m_name(name), m_length(0), m_running(false), m_paused(false),
      m_lastID(0), m_oldTime(-1)
  {
  }

  std::string Sequence::id() const
  {
    return m_id;
  }
	
  std::string Sequence::name() const
  {
    return m_name;
  }

  int Sequence::actionTime(int id) const
  {
    ActionMap::const_iterator it = m_actionMap.find(id);

    if (it == m_actionMap.end())
      {
	throw std::runtime_error("Mirssssssssss");
      }

    return it->second->time();
  }

  void Sequence::setID(const std::string& id)
  {
    m_id = id;
  }

  void Sequence::setName(const std::string& name)
  {
    m_name=name;
  }
	
  int Sequence::addAction(const std::string& command, int time)
  {
    utils::AutoPtr<Action> newAction(new Action(command, time));
		
    if (time > m_length)
      m_length = time;

    m_actionMap[++m_lastID] = newAction;

    m_sortedActions.push_back(std::make_pair(m_lastID,newAction));

    std::sort(m_sortedActions.begin(),m_sortedActions.end(),
	      ActionPairCompare());

    return m_lastID;
  }

  class SameID
  {
  public:
    SameID(int id) : m_id(id) {}
    bool operator()(const std::pair<int,utils::AutoPtr<Action> >& p)
    {
      return p.first == m_id;
    }

  private:
    int m_id;
  };

  void Sequence::deleteAction(int id)
  {
    ActionMap::iterator it = m_actionMap.find(id);
    std::vector<ActionPair>::iterator 
      it2 = std::find_if(m_sortedActions.begin(),
			 m_sortedActions.end(),SameID(id));

    if (it == m_actionMap.end() || it2 == m_sortedActions.end())
      throw std::runtime_error("id doesnt exist at Sequence::removeAction()");

    m_actionMap.erase(it);
    m_sortedActions.erase(it2);
  }
	
  void Sequence::changeActionTime(int id, int newTime)
  {
    ActionMap::iterator it = m_actionMap.find(id);

    if (it == m_actionMap.end())
      throw std::runtime_error("id doesnt exist at "
			       "Sequence::changeActionTime()");

    it->second->setTime(newTime);
  }
	
	
  void Sequence::start()
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "sequencer started" << std::endl;
#endif
    if (!m_running && !m_paused)
      {
	m_startTime = clock2Ms(clock());
	m_running = true;
      }
    else if (m_paused)
      {
	m_paused = false;
	m_running = true;
	m_startTime += clock2Ms(clock()) - m_pausedTime;
      }
  }
	
  void Sequence::stop()
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "sequencer stopped" << std::endl;
#endif
    if (m_running || m_paused)
      {
	m_running = false;
	m_paused = false;
	m_oldTime = -1;
      }
  }
	
  void Sequence::pause()
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "sequencer paused" << std::endl;
#endif
    if (m_running && !m_paused)
      {
	m_pausedTime = clock2Ms(clock());
	m_paused = true;      
	m_running = false;
      }
  }
	
  int Sequence::pendingActions(std::list<std::string>& actions)
  {
    int time = (clock2Ms(clock()) - m_startTime);//% getLength();

    for (std::vector<ActionPair>::const_iterator it = m_sortedActions.begin();
	 it != m_sortedActions.end(); ++it)
      {
	if (m_oldTime < it->second->time() && it->second->time() <= time)
	  {
	    actions.push_back(it->second->command());
	  }
	else if (it->second->time() > time)
	  break;
      }

    m_oldTime = time;
    return time;
  }

  Sequence::const_iterator Sequence::begin() const
  {
    return m_sortedActions.begin();
  }

  Sequence::const_iterator Sequence::end() const
  {
    return m_sortedActions.end();
  }

  bool Sequence::running() const
  {
    return m_running;
  }

  void Sequence::jumpTo(int newTime)
  {
    m_startTime = clock2Ms(clock()) - newTime;
    m_oldTime = m_startTime;

    //TODO: check wether the time is in range or something
  }
	
  /*----------------------Sequence-------------------------------------------*/
	
}// end of namespace
