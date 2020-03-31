#pragma once

#include "BaseMsg.h"

class CAggregateMessage : public CBaseMsg
{
public:
	CAggregateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CAggregateMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};
