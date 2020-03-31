#pragma once

#include "BaseMessage.h"

class CAbortMessage : public CBaseMessage
{
public:
	CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CAbortMessage();

	//BaseMessage
	RtmpMessageType GetType();
	void Inform();
};