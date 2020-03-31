#include "CommandMessage.h"

CCommandMessage::CCommandMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CCommandMessage::~CCommandMessage()
{

}

RtmpMessageType CCommandMessage::GetType()
{
	return RtmpMessageType::COMMAND_MESSAGE;
}

void CCommandMessage::Inform()
{

}