#include "controlvaluereceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ControlValueReceiverNet::ControlValueReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ControlValueReceiverNet::~ControlValueReceiverNet()
{}

void ControlValueReceiverNet::controlValueChanged( int nodeID, int intputIndex, const utils::Buffer& newValue )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << nodeID << ' '  << intputIndex << ' '  << newValue;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ControlValueReceiverNet::syncInputValuesStarted(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ControlValueReceiverNet::syncInputValuesFinished(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

