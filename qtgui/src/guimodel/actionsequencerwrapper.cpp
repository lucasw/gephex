#include "actionsequencerwrapper.h"

#include "interfaces/isequencercontrolreceiver.h"
#include "iscenechangelistener.h"

//TODO: remove if better error handling is available
#include <iostream>

namespace gui
{
  struct ActionInfo
  {
    ActionInfo(int id_, int time_, const std::string& command_) 
      : id(id_), time(time_), command(command_) {}
		
    int id;
    int time;
    std::string command;
  };
	
  ActionSequencerWrapper::ActionSequencerWrapper()
    : scr(0), scl(0), nopID(-1), m_loopOn(false)
  {
  }
	
  ActionSequencerWrapper::~ActionSequencerWrapper()
  {
  }
	
  void ActionSequencerWrapper::registerSequencerControlReceiver(ISequencerControlReceiver& r)
  {
    scr = &r;
  }
	
  void ActionSequencerWrapper::registerSceneChangeListener(ISceneChangeListener& l)
  {
    scl = &l;
  }
	
  namespace
  {
    /**
     * Finds a scene after begin based on the id given.
     * begin must be a forward iterator.
     * The elements over which is iterated must support ->id.
     * @param begin the iterator where the search starts
     * @param end the iterator that bounds the search (end is not searched)
     * @param pos (return by parameter) stores the position of the scene
     *            or -1 if the scene was not found
     * @return an Iterator (the first found) to an element with the right id,
     *         or end if none was found
     */
    template <class Iterator>
    Iterator findActionByID(const Iterator& begin, const Iterator& end, int id,
			    int& pos)
    {
      Iterator it = begin;
      pos = 0;
      for (;it != end; ++it, ++pos)
	{
	  if ((*it)->id == id)
	    return it;
	}
			
      pos = -1;
      return end;
    }
		
    /**
     * Inserts a new ActionInfo into the ActionMap and the (sorted)
     * ActionList.
     * If the id is already in the map nothing is done.
     * @param newInfo pointer to the ActionInfo that has been inserted.
     * @param id the id of the new scene
     * @param time the time of the action that corresponds to the new
     *        scene
     * @param actions a map of all actions with the id as key.
     * @param sortedActions a list of actions sorted by the action
     *                     time of the corresponding action.
     *                     Both (map and list) contain pointers
     *                     to the same set of sceneinfos.
     * @param length (return by value) contains the length of the 
     *               inserted scene after the function returns.
     *               If the new scene is the last scene (i.e. hat the
     *               largest time value), it contains -1. If the id
     *               already was in the map, it contains -1, too.
     * @return the position in sortedActions before which the new Action
     *         has been inserted, or -1 if the id already was in the map
     */
    int insertAction(ActionSequencerWrapper::ActionInfoPtr& newInfo,
		     int id, int time,
		     ActionSequencerWrapper::ActionMap& actions,
		     ActionSequencerWrapper::ActionList& sortedActions,
		     int& length, int nopID)
    {
      ActionSequencerWrapper::ActionMap::const_iterator it = actions.find(id);
			
      if (it != actions.end()) // is the id already in the map?
	{
	  length = -1;
	  return -1;
	}
			
      // insert the new scene into the map
      bool b 
	= actions.insert(ActionSequencerWrapper::ActionMap::value_type(id,
								       newInfo)).second;
			
      assert(b); // the inserted id didnt exist before
			
			
      // look for the right place to insert the scene into the
      // sorted scene list
      ActionSequencerWrapper::ActionList::iterator 
	sit = sortedActions.begin();
			
      int pos = 0;
      for (; sit != sortedActions.end(); ++sit)
	{
	  if ((*sit)->id != nopID) // dont count the nop
	    ++pos;	  
	  if ((*sit)->time >= time)
	    break;
	}
			
      if (sit != sortedActions.end()) // the scene is not at the end
	{
	  ActionSequencerWrapper::ActionList::iterator newIt 
	    = sortedActions.insert(sit,newInfo);
				
	  length = (*sit)->time - (*newIt)->time;
	}
      else // the scene is at the end of the list
	{
	  length = -1;
	  sortedActions.push_back(newInfo);
	}
			
      return pos;      
    }
		
    /**
     * Advances a forward iterator index times or until it reaches end.     
     */
    template <class Iterator>
    Iterator findElemAt(const Iterator& begin,const Iterator& end, int index)
    {
      Iterator it = begin;
      int i;
      for (i = 0; i < index && it != end; ++i, ++it);
			
      assert( it == end || i == index );
      return it;	
    }
  }
  
  void ActionSequencerWrapper::appendScene(const std::string& content,
					   int length)
  {
    int sumLength = 0;
	  
    if (!m_sortedActions.empty())
      sumLength = m_sortedActions.back()->time;
    if (nopID == -1)
      {
	// insert an synthetic "nop" action at the end.
	// this is done to store the length of the last scene.
	if (m_loopOn)
	  scr->addAction("jump:0",sumLength + length);
	else
	  scr->addAction("nop",sumLength + length);
      }
    else
      {
	// move the "nop" action to the end
	scr->changeActionTime(nopID, sumLength + length);
      }
	  
    scr->addAction(content, sumLength);
  }
  
  void ActionSequencerWrapper::deleteScene(int id)
  {
    if (id == nopID)
      {
	throw std::runtime_error("invalid scene id at "
				 "ActionSequencerWrapper::deleteScene()");
      }

    int pos = -1;
    ActionList::iterator it = findActionByID(m_sortedActions.begin(),
					     m_sortedActions.end(),
					     id,pos);

    if (it == m_sortedActions.end())
      {
	throw std::runtime_error("invalid scene id at "
				 "ActionSequencerWrapper::deleteScene()");
      }

    ActionList::iterator next = it;
    ++next;
    
    //TODO: testen auf nopID oder auf letzt aktion?
    if (next != m_sortedActions.end() && (*next)->id == nopID)
      {
	int time = (*it)->time;
	scr->deleteAction(id);
	scr->changeActionTime(nopID,time);
      }
    else
      {
	scr->deleteAction(id);
      }

  }
  
  void ActionSequencerWrapper::changeSceneLength(int id,
						 int newLength)
  {
    int pos;
    ActionList::const_iterator it = findActionByID(m_sortedActions.begin(),
						   m_sortedActions.end(),
						   id,pos);
	  
    if (it == m_sortedActions.end())
      {
	//TODO
	std::cerr << "no such scene at "
	  "ActionSequencerWrapper::changeSceneLength()" << std::endl;
      }
    else
      {
	ActionList::const_iterator next = it;
	++next;
		  
	if (next == m_sortedActions.end())
	  {
	    //TODO
	    std::cerr << "no next scene at "
	      "ActionSequencerWrapper::changeSceneLength()" << std::endl;
	  }
	else
	  {
	    int oldLength = (*next)->time - (*it)->time;
	    int diffLength = newLength - oldLength;
			  
	    // change the time for all actions that are behind it
	    for (; next != m_sortedActions.end(); ++next)
	      {
		scr->changeActionTime((*next)->id, (*next)->time+diffLength);
	      }
	  }
      }
  }
  
  
  void ActionSequencerWrapper::actionTimeChanged( int id, int newTime )
  {
    int pos;
    ActionList::iterator it = findActionByID(m_sortedActions.begin(),
					     m_sortedActions.end(), id, pos);
    (*it)->time = newTime;
    ActionList::const_iterator oldBefore = it;
    ActionList::const_iterator oldNext = it;
    if (oldBefore != m_sortedActions.begin())
      --oldBefore;
	  
    ++oldNext;
	  
    if (it == m_sortedActions.end())
      {
	//TODO
	std::cerr << "bubu abab" << std::endl;
      }
	  
    assert(newTime >= 0);
	  
    int i = 0;
    ActionList::const_iterator before = it;
    if (before != m_sortedActions.begin())
      --before;
    ActionList::const_iterator next = it;
    int numberOfScenes = m_sortedActions.size()-1;
	  
    // run through all actions and find the two actions
    // before and next that are before and after the new position
    // of the scene id.
    // if next == end there is no new scene
    for (;i < numberOfScenes; ++i, ++before, ++next) //TODO, doesnt work
      {
	assert(before != m_sortedActions.end());
	++next;
		  
	if (i == pos) //ignore the scene that has changed
	  continue;
		  
	if (newTime >= (*before)->time 
	    && (next == m_sortedActions.end() || newTime <= (*next)->time))
	  break;
      }
	  
    // now the new place of the scene is between i and i_
    // (if i_ < numberOfScenes) or after i (if i_ >= numberOfScenes)
    //    assert (i != pos);
    assert ((*before)->time <= (*it)->time);
    assert( next == m_sortedActions.end() || (*it)->time <= (*next)->time);
	  
    if ((*before)->id != nopID)
      scl->sceneLengthChanged((*before)->id,(*it)->time - (*before)->time);
	  
    if (next == m_sortedActions.end()) //the action is the end marker
      {
	// do we have a new end marker or was id the end marker before?
	if (oldNext != m_sortedActions.end())
	  {
	    // new end marker
	    scl->sceneDeleted(id);
	    scl->sceneInserted((*before)->id, pos,
			       (*before)->command, newTime - (*before)->time);
	  }
      }
    else // the scene is inside
      {
	if (id != nopID)
	  scl->sceneLengthChanged(id,(*next)->time - (*it)->time);
		  
	if (i+1 == pos)
	  {
	    //scene does not move
	    assert(oldBefore == before && oldNext == next);
	  }
	else
	  {
	    //scene must be moved
	    assert(i+1 != pos);
	    //			  assert(oldBefore != before && oldNext != next);
			  
	    if (i < pos)
	      {	    
		scl->sceneMoved(id,i+1);
	      }
	    if (i > pos)
	      {
		scl->sceneMoved(id,i);
	      }
			  
	    if (pos != 0)
	      scl->sceneLengthChanged((*oldBefore)->id,
				      (*oldNext)->time - (*oldBefore)->time);
	  }
      }
	  
	  
  }
  
  void ActionSequencerWrapper::actionDeleted( int id )
  {
    int pos = -1;
    ActionMap::iterator it = m_actions.find(id);
    ActionList::iterator it2 = findActionByID(m_sortedActions.begin(),
					      m_sortedActions.end(),
					      id,pos);
	  
    if (id == nopID)
      {
	//TODO
	//assert(!"nop deleted");
	nopID = -1;
      }
	  
    if (it == m_actions.end() || it2 == m_sortedActions.end())
      {
	//TODO
	//log message or something
	std::cerr << "no such scene at "
	  "ActionSequencerWrapper::actionDeleted( int id )" << std::endl;
      }
	  
    // tell the view, if it was not the last action
    if (m_sortedActions.back()->id != id)
      scl->sceneDeleted(id);    
	  
    m_actions.erase(it);
    m_sortedActions.erase(it2);
	  
    //TODO: update end Marker
  }
  
  
  void ActionSequencerWrapper::actionAdded( int id, const std::string& command,
					    int time )
  {
    ActionInfoPtr newInfo ( new ActionInfo(id,time,command) );
	  
    int length = -1;
    int pos = insertAction(newInfo, id, time,
			   m_actions, m_sortedActions, length, nopID);
	  
    if (pos == -1) // did insert succeed?
      {
	//TODO
	std::cerr << "could not insert scene at "
	  "ActionSequencerWrapper::actionAdded()" << std::endl;
      }
    else 
      {
	if (length != -1) // was it inserted "inside" the list?
	  {
	    // yes, tell the view about it
	    scl->sceneInserted(id,pos,command,length);
			  
	    if (pos != 0)
	      {
		// notify the view, that the length of the scene before 
		// the new scene has changed
				  
		ActionSequencerWrapper::ActionList::iterator 
		  before = findElemAt(m_sortedActions.begin(), 
				      m_sortedActions.end(), pos-1);
		assert( before != m_sortedActions.end() );
				  
		ActionSequencerWrapper::ActionList::iterator next = before;
		++next;
		assert( next != m_sortedActions.end() );
				  
		int id_ = (*before)->id;
		int newLength = (*next)->time - (*before)->time;
				  
		assert(newLength >= 0);
		assert((*next)->time == time);
				  
		scl->sceneLengthChanged(id_, newLength);
	      }
	  }
	else 
	  {
	    if (command == "nop" || command == "jump:0") //TODO
	      nopID = id;
			  
	    if (pos != 0) //was it inserted at the end, but not at the start?
	      {
		// yes, dont't tell the view about it (the size is undefined!)
		// instead tell the view, that the scene before has been inserted
		ActionSequencerWrapper::ActionList::iterator 
		  before = findElemAt(m_sortedActions.begin(), 
				      m_sortedActions.end(), pos-1);
		assert( before != m_sortedActions.end() );
				  
		int id_ = (*before)->id;
		std::string command_ = (*before)->command;
		int length_ = time - (*before)->time;
		scl->sceneInserted(id_,pos-1,command_,length_ );
	      }	    
	  }
      }
  }

  void ActionSequencerWrapper::loop(bool sloop)
  {
    if (m_loopOn && !sloop)
      {
	//turn off loop
	if (nopID != -1)
	  {
	    ActionMap::const_iterator it = m_actions.find(nopID);
	    if (it == m_actions.end())
	      {
		throw std::runtime_error("invalid nopID at "
					 "ActionSequencerWrapper::loop()");
	      }

	    int time = it->second->time;
	    scr->deleteAction(nopID);
	    scr->addAction("nop",time);
	  }

	
      }
    else if (!m_loopOn && sloop)
      {
	//turn on loop

	if (nopID != -1)
	  {
	    ActionMap::const_iterator it = m_actions.find(nopID);
	    if (it == m_actions.end())
	      {
		throw std::runtime_error("invalid nopID at "
					 "ActionSequencerWrapper::loop()");
	      }

	    int time = it->second->time;
	    scr->deleteAction(nopID);
	    scr->addAction("jump:0",time);
	  }
      }
  }
  
}
