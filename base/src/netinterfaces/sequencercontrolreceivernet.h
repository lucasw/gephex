#ifndef INCLUDED_SEQUENCERCONTROLRECEIVERNET_H
#define INCLUDED_SEQUENCERCONTROLRECEIVERNET_H

#include "interfaces/isequencercontrolreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class SequencerControlReceiverNet : public ISequencerControlReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	SequencerControlReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~SequencerControlReceiverNet();

	void createSequence( const std::string& sequenceName );

	void saveSequence( const std::string& id );

	void changeSequence( const std::string& id );

	void deleteSequence( const std::string& id );

	void renameSequence( const std::string& id, const std::string& newName );

	void start(  );

	void pause(  );

	void stop(  );

	void addAction( const std::string& command, int time );

	void changeActionTime( int id, int newTime );

	void deleteAction( int id );

};
#endif
