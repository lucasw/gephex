#include "errorsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/ierrorreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ErrorSenderNet::ErrorSenderNet()
	 : m_rec(0) {}

void ErrorSenderNet::registerErrorReceiver(IErrorReceiver& r)
{
	m_rec = &r;
}

void ErrorSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ErrorSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String text;
		bs  >> text;
		m_rec->error( text );
	 }
	else 	if (command == "0001")
	 {
		utils::String text;
		bs  >> text;
		m_rec->warning( text );
	 }
	else 	if (command == "0002")
	 {
		utils::String text;
		bs  >> text;
		m_rec->log( text );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at Error";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

