#include "sequencerstatussendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/isequencerstatusreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequencerStatusSenderNet::SequencerStatusSenderNet()
	 : m_rec(0) {}

void SequencerStatusSenderNet::registerSequencerStatusReceiver(ISequencerStatusReceiver& r)
{
	m_rec = &r;
}

void SequencerStatusSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "SequencerStatusSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String sequenceID;
		bs  >> sequenceID;
		m_rec->editSequenceChanged( sequenceID );
	 }
	else 	if (command == "0001")
	 {
		m_rec->started(  );
	 }
	else 	if (command == "0002")
	 {
		m_rec->stopped(  );
	 }
	else 	if (command == "0003")
	 {
		m_rec->paused(  );
	 }
	else 	if (command == "0004")
	 {
		int currentTime;
		bs  >> currentTime;
		m_rec->time( currentTime );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at SequencerStatus";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

