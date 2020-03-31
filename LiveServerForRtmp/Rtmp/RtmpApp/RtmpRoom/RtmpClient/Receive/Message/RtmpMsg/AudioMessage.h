#pragma once

#include "BaseMsg.h"

class CAudioMessage : public CBaseMsg
{
public:
	CAudioMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CAudioMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};