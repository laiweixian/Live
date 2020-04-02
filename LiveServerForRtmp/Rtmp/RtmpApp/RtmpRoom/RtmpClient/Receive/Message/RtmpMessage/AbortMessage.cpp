#include "AbortMessage.h"

CAbortMessage::CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :
	CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CAbortMessage::~CAbortMessage()
{

}

RtmpMessageType CAbortMessage::GetType()
{
	return RtmpMessageType::ABORT_MESSAGE;
}

