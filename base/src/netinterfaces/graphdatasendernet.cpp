#include "graphdatasendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/igraphdatareceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
GraphDataSenderNet::GraphDataSenderNet()
	 : m_rec(0) {}

void GraphDataSenderNet::registerGraphDataReceiver(IGraphDataReceiver& r)
{
	m_rec = &r;
}

void GraphDataSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "GraphDataSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		int type;
		utils::Buffer buf;
		bs  >> type >> buf;
		m_rec->graphDataSet( type, buf );
	 }
	else 	if (command == "0001")
	 {
		int type;
		bs  >> type;
		m_rec->graphDataUnSet( type );
	 }
	else 	if (command == "0002")
	 {
		m_rec->syncGraphDataStarted(  );
	 }
	else 	if (command == "0003")
	 {
		m_rec->syncGraphDataFinished(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at GraphData";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

