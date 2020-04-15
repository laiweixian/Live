#include "AudioMessage.h"

CAudioMessage::CAudioMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CAudioMessage::~CAudioMessage()
{

}

CBaseMessage::MessageType CAudioMessage::GetType()
{
	return CBaseMessage::MessageType::AUDIO_MESSAGE;
}

