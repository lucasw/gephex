#include "sequencercontrolsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/isequencercontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequencerControlSenderNet::SequencerControlSenderNet()
	 : m_rec(0) {}

void SequencerControlSenderNet::registerSequencerControlReceiver(ISequencerControlReceiver& r)
{
	m_rec = &r;
}

void SequencerControlSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "SequencerControlSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String sequenceName;
		bs  >> sequenceName;
		m_rec->createSequence( sequenceName );
	 }
	else 	if (command == "0001")
	 {
		utils::String id;
		bs  >> id;
		m_rec->saveSequence( id );
	 }
	else 	if (command == "0002")
	 {
		utils::String id;
		bs  >> id;
		m_rec->changeSequence( id );
	 }
	else 	if (command == "0003")
	 {
		utils::String id;
		bs  >> id;
		m_rec->deleteSequence( id );
	 }
	else 	if (command == "0004")
	 {
		utils::String id;
		utils::String newName;
		bs  >> id >> newName;
		m_rec->renameSequence( id, newName );
	 }
	else 	if (command == "0005")
	 {
		m_rec->start(  );
	 }
	else 	if (command == "0006")
	 {
		m_rec->pause(  );
	 }
	else 	if (command == "0007")
	 {
		m_rec->stop(  );
	 }
	else 	if (command == "0008")
	 {
		utils::String command;
		int time;
		bs  >> command >> time;
		m_rec->addAction( command, time );
	 }
	else 	if (command == "0009")
	 {
		int id;
		int newTime;
		bs  >> id >> newTime;
		m_rec->changeActionTime( id, newTime );
	 }
	else 	if (command == "0010")
	 {
		int id;
		bs  >> id;
		m_rec->deleteAction( id );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at SequencerControl";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

