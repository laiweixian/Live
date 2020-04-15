#include "CommandMessage.h"

CCommandMessage::CCommandMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CCommandMessage::~CCommandMessage()
{

}

CBaseMessage::MessageType CCommandMessage::GetType()
{
	return CBaseMessage::MessageType::COMMAND_MESSAGE;
}

