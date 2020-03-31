#pragma once

#include "BaseMessage.h"

class CAggregateMessage : public CBaseMessage
{

public:
	CAggregateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CAggregateMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};
