#pragma once

#include "BaseMessage.h"

class CCommandMessage : public CBaseMessage
{
public:
	CCommandMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CCommandMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};