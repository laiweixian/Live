#include "VideoMessage.h"

CVideoMessage::CVideoMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CVideoMessage::~CVideoMessage()
{

}

CBaseMessage::MessageType CVideoMessage::GetType()
{
	return CBaseMessage::MessageType::VIDEO_MESSAGE;
}

