#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId),m_Content({0})
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

CWindowAcknowledgementSize::Content CWindowAcknowledgementSize::GetContent()
{
	uint32_t acknowledgementWindowSize = 0;
	memcpy(&acknowledgementWindowSize, m_Payload.buff, 4);

	m_Content.acknowledgementWindowSize = ::BigToHost32(&acknowledgementWindowSize);
	return m_Content;
}



CBaseMessage::MessageType CWindowAcknowledgementSize::GetType()
{
	return CBaseMessage::MessageType::WINDOW_ACKNOWLEDGEMENT_SIZE;
}

