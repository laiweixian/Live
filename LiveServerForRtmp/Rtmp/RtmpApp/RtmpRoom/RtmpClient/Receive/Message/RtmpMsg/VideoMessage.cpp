#include "VideoMessage.h"

CVideoMessage::CVideoMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform) :\
CBaseMsg(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CVideoMessage::~CVideoMessage()
{

}

RtmpMessageType CVideoMessage::GetType()
{
	return RtmpMessageType::VIDEO_MESSAGE;
}

void CVideoMessage::Inform()
{

}