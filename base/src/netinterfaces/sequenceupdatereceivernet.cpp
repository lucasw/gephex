#include "sequenceupdatereceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequenceUpdateReceiverNet::SequenceUpdateReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

SequenceUpdateReceiverNet::~SequenceUpdateReceiverNet()
{}

void SequenceUpdateReceiverNet::actionTimeChanged( int id, int newTime )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << id << ' '  << newTime;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void SequenceUpdateReceiverNet::actionDeleted( int id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << id;
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void SequenceUpdateReceiverNet::actionAdded( int id, const std::string& command, int time )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << id << ' '  << utils::String(command) << ' '  << time;
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

