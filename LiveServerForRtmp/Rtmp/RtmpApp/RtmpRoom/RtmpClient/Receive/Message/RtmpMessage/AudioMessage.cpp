#include "AudioMessage.h"

CAudioMessage::CAudioMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CAudioMessage::~CAudioMessage()
{

}

RtmpMessageType CAudioMessage::GetType()
{
	return RtmpMessageType::AUDIO_MESSAGE;
}

void CAudioMessage::Inform()
{

}