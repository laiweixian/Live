#pragma once

#include "BaseMessage.h"

class CAudioMessage : public CBaseMessage
{
public:
	CAudioMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CAudioMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};