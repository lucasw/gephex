#include "graphnamesendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/igraphnamereceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
GraphNameSenderNet::GraphNameSenderNet()
	 : m_rec(0) {}

void GraphNameSenderNet::registerGraphNameReceiver(IGraphNameReceiver& r)
{
	m_rec = &r;
}

void GraphNameSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "GraphNameSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String graphID;
		utils::String snapID;
		utils::String graphName;
		utils::String snapName;
		bs  >> graphID >> snapID >> graphName >> snapName;
		m_rec->graphExists( graphID, snapID, graphName, snapName );
	 }
	else 	if (command == "0001")
	 {
		utils::String graphID;
		utils::String snapID;
		bs  >> graphID >> snapID;
		m_rec->graphNoLongerExists( graphID, snapID );
	 }
	else 	if (command == "0002")
	 {
		utils::String graphID;
		utils::String snapID;
		utils::String newGraphName;
		utils::String newSnapName;
		bs  >> graphID >> snapID >> newGraphName >> newSnapName;
		m_rec->graphRenamed( graphID, snapID, newGraphName, newSnapName );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at GraphName";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

