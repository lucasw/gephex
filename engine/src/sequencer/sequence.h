#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include <string>
#include <map>
#include <vector>
#include <list>

#include "utils/autoptr.h"

class ISequenceUpdateReceiver;

namespace sequencer
{

  class Action
    {
    private:
      std::string m_command;
      int m_time;

    public:
      //	Action();
      Action(const std::string& command, int time);

      std::string command() const;
      int time() const;

      void setTime(int);
    };

  /*class SequenceIterator
    {
    public:
    SequenceIterator(std::vector<Sequence::ActionPair>& actions);


    private:

    std::vector<Sequence::ActionPair>& m_actions;
    };*/

  class Sequence
    {
    public:
      typedef std::pair<int,utils::AutoPtr<Action> > ActionPair;
      typedef std::vector<ActionPair>::const_iterator const_iterator;
	

      Sequence(const std::string& id, const std::string& name);

      std::string id() const;

      std::string name() const;    

      int actionTime(int id) const;

      void setID(const std::string& id);

      void setName(const std::string&);      

      int addAction(const std::string& command, int time);

      void deleteAction(int id);
        
      void changeActionTime(int id, int newTime);

      void start();
      void stop();
      void pause();

      // haengt die seit dem letzten Aufruf auszufuehrenden 
      // kommandos an actions an
      int pendingActions(std::list<std::string>& actions);

      const_iterator begin() const;
      const_iterator end() const;

      bool running() const;

      bool paused() const;

      void jumpTo(int newTime);

    private:
      std::string m_id;
      std::string m_name;
      typedef std::map<int,utils::AutoPtr<Action> > ActionMap;
      ActionMap m_actionMap;
	
      std::vector<ActionPair> m_sortedActions;
	
      int m_length;
      int m_startTime;
      int m_pausedTime;

      bool m_running;
      bool m_paused;

      int m_lastID;
      int m_oldTime;
  
    };

}

#endif
