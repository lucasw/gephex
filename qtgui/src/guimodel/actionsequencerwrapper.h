#ifndef INCLUDED_ACTION_SEQUENCER_WRAPPER_H
#define INCLUDED_ACTION_SEQUENCER_WRAPPER_H

#include <map>
#include <list>

#include "iscenesequencer.h"
#include "interfaces/isequenceupdatereceiver.h"
#include "interfaces/isequencercontrolsender.h"
#include "interfaces/isequenceupdatereceiver.h"

#include "utils/autoptr.h"

namespace gui
{
	
  class ISceneChangeListener;

  struct ActionInfo;
	
  /**
   * This interface wraps the isequencercontrolreceiver interface
   * (which is based on actions at specific points of time)
   * behind a ISceneSequencer interface (which is based on a list of
   * scenes, each with a certain length).
   */
  class ActionSequencerWrapper : public ISceneSequencer,
				 public ISequencerControlSender,
				 public ISequenceUpdateReceiver
  {
  public:

    ActionSequencerWrapper();
    ~ActionSequencerWrapper();
		
    virtual void registerSequencerControlReceiver(ISequencerControlReceiver& r);		
    void registerSceneChangeListener(ISceneChangeListener& l);
		

    // methods from ISceneSequencer
		
    virtual void appendScene(const std::string& content, int length);
		
    virtual void deleteScene(int id);
		
    virtual void changeSceneLength(int id, int newLength);
		

    // methods from ISequencerControlSender		
		
    virtual void actionTimeChanged( int id, int newTime );
		
    virtual void actionDeleted( int id );
		
    virtual void actionAdded( int id, const std::string& command,
			      int time );

    virtual void loop(bool loop);
		
    //TODO: bad, dont expose impl. details in the public interface
    typedef utils::AutoPtr<ActionInfo> ActionInfoPtr;
    typedef std::map<int, ActionInfoPtr> ActionMap;
    typedef std::list<ActionInfoPtr> ActionList;
		
  private:
    ISequencerControlReceiver* scr;
    ISceneChangeListener* scl;

    ActionMap m_actions;
    ActionList m_sortedActions;
    int nopID;
    bool m_loopOn;
  };
	
}
#endif
