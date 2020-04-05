#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

uint32_t CWindowAcknowledgementSize::GetAcknowledgementWindowSize()
{
	uint32_t acknowledgementWindowSize = 0;
	memcpy(&acknowledgementWindowSize,m_Payload.buff,4);

	acknowledgementWindowSize = ::BigToHost32(&acknowledgementWindowSize);
	return acknowledgementWindowSize;
}

RtmpMessageType CWindowAcknowledgementSize::GetType()
{
	return RtmpMessageType::WINDOW_ACKNOWLEDGEMENT_SIZE;
}

