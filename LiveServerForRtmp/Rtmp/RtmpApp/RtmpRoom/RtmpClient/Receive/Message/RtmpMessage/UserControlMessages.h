#pragma once

#include "BaseMessage.h"

class CUserControlMessages : public CBaseMessage
{
public:
	CUserControlMessages(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CUserControlMessages();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};