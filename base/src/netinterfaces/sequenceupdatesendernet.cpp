#include "sequenceupdatesendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/isequenceupdatereceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequenceUpdateSenderNet::SequenceUpdateSenderNet()
	 : m_rec(0) {}

void SequenceUpdateSenderNet::registerSequenceUpdateReceiver(ISequenceUpdateReceiver& r)
{
	m_rec = &r;
}

void SequenceUpdateSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "SequenceUpdateSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		int id;
		int newTime;
		bs  >> id >> newTime;
		m_rec->actionTimeChanged( id, newTime );
	 }
	else 	if (command == "0001")
	 {
		int id;
		bs  >> id;
		m_rec->actionDeleted( id );
	 }
	else 	if (command == "0002")
	 {
		int id;
		utils::String command;
		int time;
		bs  >> id >> command >> time;
		m_rec->actionAdded( id, command, time );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at SequenceUpdate";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

