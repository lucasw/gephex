#include "graphnamereceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
GraphNameReceiverNet::GraphNameReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

GraphNameReceiverNet::~GraphNameReceiverNet()
{}

void GraphNameReceiverNet::graphExists( const std::string& graphID, const std::string& snapID, const std::string& graphName, const std::string& snapName )
{
	utils::Buffer temp_buf_(64);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID) << ' '  << utils::String(graphName) << ' '  << utils::String(snapName);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void GraphNameReceiverNet::graphNoLongerExists( const std::string& graphID, const std::string& snapID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void GraphNameReceiverNet::graphRenamed( const std::string& graphID, const std::string& snapID, const std::string& newGraphName, const std::string& newSnapName )
{
	utils::Buffer temp_buf_(64);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID) << ' '  << utils::String(newGraphName) << ' '  << utils::String(newSnapName);
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

