#ifndef __INCLUDED_SEQUENCER_H__
#define __INCLUDED_SEQUENCER_H__

#include <map>

#include "interfaces/imodelcontrolsender.h"
#include "interfaces/isequencercontrolreceiver.h"
#include "interfaces/isequenceupdatesender.h"
#include "interfaces/isequencenamesender.h"
#include "interfaces/isequencerstatussender.h"

#include "interfaces/itask.h"

#include "utils/autoptr.h"

namespace sequencer
{

  class Sequence;
  class SequenceFileSystem;

  class Sequencer: 
    public IModelControlSender, 
    public ISequencerControlReceiver,
    public ISequenceUpdateSender,
    public ISequenceNameSender,
    public ISequencerStatusSender,
    public ITask
  
  {
  public:
    Sequencer(const std::string& basePath);
    virtual ~Sequencer();

    virtual void createSequence(const std::string& sequenceName);

    virtual void saveSequence(const std::string& id);
	    
    virtual void changeSequence(const std::string& id);

    virtual void deleteSequence(const std::string& id);

    virtual void renameSequence(const std::string& id,
				const std::string& newName);
    
    virtual void start();
	
    virtual void pause();

    virtual void stop();

    virtual void addAction(const std::string& command, int time);

    virtual void changeActionTime(int id, int newTime);

    virtual void deleteAction(int id);

    virtual bool run();

    void updateFileSystem();

    void registerModelControlReceiver(IModelControlReceiver&);
    void registerSequenceUpdateReceiver(ISequenceUpdateReceiver&);
    void registerSequenceNameReceiver(ISequenceNameReceiver& r);
    void registerSequencerStatusReceiver(ISequencerStatusReceiver& r);

  private:    

    IModelControlReceiver* mcr;
    ISequenceUpdateReceiver* sur;
    ISequenceNameReceiver* snr;
    ISequencerStatusReceiver* ssr;

    typedef std::map<std::string,utils::AutoPtr<Sequence> > SequenceMap;
    SequenceMap allSequences;

    utils::AutoPtr<Sequence> current;

    utils::AutoPtr<SequenceFileSystem> fileSystem;

    std::map<std::string,bool> knownIDs;
  };

} // end of namesapce

#endif

