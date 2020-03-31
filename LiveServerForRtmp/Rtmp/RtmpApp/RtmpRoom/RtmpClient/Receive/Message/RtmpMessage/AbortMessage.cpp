#include "AbortMessage.h"

CAbortMessage::CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform) :
	CBaseMessage(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CAbortMessage::~CAbortMessage()
{

}

RtmpMessageType CAbortMessage::GetType()
{
	return RtmpMessageType::ABORT_MESSAGE;
}

void CAbortMessage::Inform()
{

}