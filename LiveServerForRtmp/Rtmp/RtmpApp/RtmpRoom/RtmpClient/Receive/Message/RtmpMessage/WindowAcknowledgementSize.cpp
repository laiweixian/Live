#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

RtmpMessageType CWindowAcknowledgementSize::GetType()
{
	return RtmpMessageType::WINDOW_ACKNOWLEDGEMENT_SIZE;
}

