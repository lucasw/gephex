#include "sequencerstatusreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequencerStatusReceiverNet::SequencerStatusReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

SequencerStatusReceiverNet::~SequencerStatusReceiverNet()
{}

void SequencerStatusReceiverNet::editSequenceChanged( const std::string& sequenceID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(sequenceID);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void SequencerStatusReceiverNet::started(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void SequencerStatusReceiverNet::stopped(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void SequencerStatusReceiverNet::paused(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

void SequencerStatusReceiverNet::time( int currentTime )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << currentTime;
	bs.flush();
	m_tagger->setTag( "0004" );
	m_tagger->send( temp_buf_ );

}

