#include "VideoMessage.h"

CVideoMessage::CVideoMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CVideoMessage::~CVideoMessage()
{

}

RtmpMessageType CVideoMessage::GetType()
{
	return RtmpMessageType::VIDEO_MESSAGE;
}

