#include "sequencenamesendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/isequencenamereceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequenceNameSenderNet::SequenceNameSenderNet()
	 : m_rec(0) {}

void SequenceNameSenderNet::registerSequenceNameReceiver(ISequenceNameReceiver& r)
{
	m_rec = &r;
}

void SequenceNameSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "SequenceNameSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String id;
		utils::String name;
		bs  >> id >> name;
		m_rec->sequenceExists( id, name );
	 }
	else 	if (command == "0001")
	 {
		utils::String id;
		bs  >> id;
		m_rec->sequenceNoLongerExists( id );
	 }
	else 	if (command == "0002")
	 {
		utils::String id;
		utils::String newName;
		bs  >> id >> newName;
		m_rec->sequenceRenamed( id, newName );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at SequenceName";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

