#include "sequencenamereceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequenceNameReceiverNet::SequenceNameReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

SequenceNameReceiverNet::~SequenceNameReceiverNet()
{}

void SequenceNameReceiverNet::sequenceExists( const std::string& id, const std::string& name )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id) << ' '  << utils::String(name);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void SequenceNameReceiverNet::sequenceNoLongerExists( const std::string& id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void SequenceNameReceiverNet::sequenceRenamed( const std::string& id, const std::string& newName )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id) << ' '  << utils::String(newName);
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

