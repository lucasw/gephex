#include "sequencercontrolreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
SequencerControlReceiverNet::SequencerControlReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

SequencerControlReceiverNet::~SequencerControlReceiverNet()
{}

void SequencerControlReceiverNet::createSequence( const std::string& sequenceName )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(sequenceName);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::saveSequence( const std::string& id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::changeSequence( const std::string& id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id);
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::deleteSequence( const std::string& id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id);
	bs.flush();
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::renameSequence( const std::string& id, const std::string& newName )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(id) << ' '  << utils::String(newName);
	bs.flush();
	m_tagger->setTag( "0004" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::start(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0005" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::pause(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0006" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::stop(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0007" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::addAction( const std::string& command, int time )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(command) << ' '  << time;
	bs.flush();
	m_tagger->setTag( "0008" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::changeActionTime( int id, int newTime )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << id << ' '  << newTime;
	bs.flush();
	m_tagger->setTag( "0009" );
	m_tagger->send( temp_buf_ );

}

void SequencerControlReceiverNet::deleteAction( int id )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << id;
	bs.flush();
	m_tagger->setTag( "0010" );
	m_tagger->send( temp_buf_ );

}

