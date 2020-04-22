#pragma once

#include "BaseMessage.h"
#include "Command/Commands.h"

/*-----------------------------------------------------------------------------------------*/
class CCommandMessage : public CBaseMessage
{
public:
	CCommandMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CCommandMessage();

	//CBaseMessage
	CBaseMessage::MessageType GetType();
};