#include "AudioMessage.h"

CAudioMessage::CAudioMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
{

}

CAudioMessage::~CAudioMessage()
{

}

RtmpMessageType CAudioMessage::GetType()
{
	return RtmpMessageType::AUDIO_MESSAGE;
}

