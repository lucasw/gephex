#include "sequencer.h"

#include <sstream>
#include <ctime>

#include "sequence.h"
#include "sequencefilesystem.h"
#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/isequenceupdatereceiver.h"
#include "interfaces/isequencenamereceiver.h"
#include "interfaces/isequencerstatusreceiver.h"

#include "utils/stringtokenizer.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

namespace sequencer
{
	
  Sequencer::Sequencer(const std::string& basePath)
    : mcr(0), sur(0), snr(0), fileSystem(new SequenceFileSystem(basePath))
  {
  }
	
  Sequencer::~Sequencer()
  {
  }
	
  namespace
  {
    void performAction(const std::string& command,
		       IModelControlReceiver* mcr,
		       Sequence& currentSequence)
    {
      if (mcr)
	{
	  utils::StringTokenizer st(command);
			
	  std::string command = st.next(":");
			
	  if (command == "changeGraph")
	    {
				
	      std::string graphName = st.next(":");
				
	      std::string controlValueSetName = st.next(" ");
				
	      mcr->changeRenderedGraph(graphName, controlValueSetName);
	    }
	  else if (command == "stop")
	    {
				//stop();
				//TODO
	    }
	  else if (command == "jump")
	    {
	      std::string sTime = st.next(":");
	      std::istringstream is(sTime);
				
	      int newTime;
	      is >> newTime;
				
	      if ( newTime < 0 )
		throw std::runtime_error("Negative time at jump");
				
	      currentSequence.jumpTo(newTime);
	    }
	  else if (command == "nop")
	    {
				// Do nothing
	    }
	  else
	    {
	      throw std::runtime_error("Command not supported at "
				       "sequencer::performAction()");
	    }
	}
      else
	{
	  throw std::runtime_error("Cant play the Sequence because the "
				   "ModelcontrolReceiver is not registered");
	}
    }

    std::string createNewID(const std::string& name,
			    std::map<std::string,bool>& knownIDs)
    {
      std::string id = name + '_';

      while (knownIDs.find(id) != knownIDs.end())
	id += '_';

      return id; 
    }

    void sendSequenceConstruction(const Sequence& sequence,
				  ISequenceUpdateReceiver* sur)
    {
      for (Sequence::const_iterator it = sequence.begin();
	   it != sequence.end(); ++it)
	{
	  Sequence::ActionPair pair = *it;
	  sur->actionAdded(pair.first, pair.second->command(),
			   pair.second->time());
	}
    }
	
    void sendSequenceDestruction(const Sequence& sequence,
				 ISequenceUpdateReceiver* sur)
    {
      for (Sequence::const_iterator it = sequence.begin();
	   it != sequence.end(); ++it)
	{
	  Sequence::ActionPair pair = *it;
	  sur->actionDeleted(pair.first);
	}
    }

  }
	
  void Sequencer::createSequence(const std::string& sequenceName)
  {
    for (SequenceMap::iterator it = allSequences.begin();
	 it != allSequences.end(); ++it)
      {
	if (it->second->name() == sequenceName)
	  throw std::runtime_error("This Name is already existing, "
				   "choose another one...!");
      }

    std::string id = createNewID(sequenceName, knownIDs);
    SequenceMap::const_iterator sit = allSequences.find(id);
    assert ( sit == allSequences.end() );
		
    utils::AutoPtr<Sequence> seq ( new Sequence(id, sequenceName) );
    allSequences[id] = seq;
		
    if (snr)
      snr->sequenceExists(id,sequenceName);
  }

  void Sequencer::saveSequence(const std::string& id)
  {
    SequenceMap::iterator it = allSequences.find(id);
		
    if (it == allSequences.end())
      {
	throw std::runtime_error("Sequence doesnt exist at "
				 "Sequencer::saveSequence()");
      }

    fileSystem->saveSequence(id, *it->second);
  }
	
	
  void Sequencer::changeSequence(const std::string& id)
  {
		
    SequenceMap::iterator it = allSequences.find(id);
    if(it == allSequences.end())
      {
	utils::AutoPtr<Sequence> newSequence( new Sequence(id,"") );
	fileSystem->loadSequence(id, *newSequence);
	allSequences[id] = newSequence;			

	it = allSequences.find(id);
      }

    assert( it != allSequences.end() );
		
    if (current)
      sendSequenceDestruction(*current,sur);
		
    current = it->second;
		
    sendSequenceConstruction(*current,sur);
    
    if (ssr)
      ssr->editSequenceChanged( id );
    //TODO: who wants to know that?
    /*    if(snr)
	  snr->sequenceChanged(name);*/
  }
	
  void Sequencer::deleteSequence(const std::string& id)
  {
    SequenceMap::iterator it = allSequences.find(id);		

    if ( it != allSequences.end() )
      {
	allSequences.erase(it);
      }

    try {
      fileSystem->deleteSequence(id);
    }
    catch (...) {} //TODO: added because some sequences are not on disc1
		
    if (snr)
      snr->sequenceNoLongerExists(id);
  }
	
  void Sequencer::renameSequence(const std::string& id,
				 const std::string& newName)
  {
    SequenceMap::const_iterator sit = allSequences.find(id);
    if (sit == allSequences.end())
      throw std::runtime_error("Sequence doesnt exists at "
			       "Sequencer::renameSequence()");

    for (SequenceMap::iterator it = allSequences.begin();
	 it != allSequences.end(); ++it)
      {
	if (it->second->name() == newName)
	  throw std::runtime_error("Name already exists at "
				   "Sequencer::renameSequence()");
      }


    sit->second->setName(newName);

    snr->sequenceRenamed(id, newName);
  }
	
  void Sequencer::start()
  {
    if (!current)
      return;

    current->start();
		
    if (ssr)
      ssr->started();
  }
	
  void Sequencer::pause()
  {
    if (!current)
      return;

    current->pause();
		
    if (ssr)
      ssr->paused();
  }
	
  void Sequencer::stop()
  {
    if (!current)
      return;

    current->stop();
		
    if (ssr)
      {
	ssr->stopped();
	ssr->time(0);
      }
  }
	
  void Sequencer::addAction(const std::string& command, int time)
  {
    if (!current)
      return;


    int id = current->addAction(command, time);
		
    if (sur)
      sur->actionAdded(id,command,time);
  }
	
  void Sequencer::changeActionTime(int id, int newTime)
  {
    if (!current)
      return;

    current->changeActionTime(id,newTime);
		
    if (sur)
      sur->actionTimeChanged(id,newTime);
  }
	
  void Sequencer::deleteAction(int id)
  {
    if (!current)
      return;


    current->deleteAction(id);
		
    if (sur)
      sur->actionDeleted(id);
  }
	
  bool Sequencer::run()
  {
    if (current != 0 && current->running())
      {
	std::list<std::string> actions;
			
	int time = current->pendingActions(actions);
			
	for (std::list<std::string>::const_iterator it = actions.begin();
	     it != actions.end(); ++it)
	  {
	    performAction(*it,mcr, *current);
	  }
			
	if (ssr)
	  ssr->time(time);
      }

    return true;
  }
	
  void Sequencer::updateFileSystem()
  {
    typedef const std::list<std::pair<std::string,std::string> > IDNamesList;
    IDNamesList	names = fileSystem->getIDsAndNames();
		
    for (IDNamesList::const_iterator it = names.begin();
	 it != names.end(); ++it)
      {
	std::string id = it->first;
#if (ENGINE_VERBOSITY > 0)
	std::cout << "sequence: " << id << ",  " 
		  << it->second << std::endl;
#endif
	if (knownIDs.find(id) != knownIDs.end())
	  throw std::runtime_error("id scheisse");
	
	knownIDs[id] = true;
	snr->sequenceExists(id, it->second);
      }
  }
	
  void Sequencer::registerModelControlReceiver(IModelControlReceiver& _mgcr)
  {
    mcr = &_mgcr;
  }
	
  void Sequencer::registerSequenceUpdateReceiver(ISequenceUpdateReceiver& _sur)
  {
    sur = &_sur;
  }
	
  void Sequencer::registerSequenceNameReceiver(ISequenceNameReceiver& r)
  {
    snr = &r;
  }

  void Sequencer::registerSequencerStatusReceiver(ISequencerStatusReceiver& r)
  {
    ssr = & r;
  }	
}
