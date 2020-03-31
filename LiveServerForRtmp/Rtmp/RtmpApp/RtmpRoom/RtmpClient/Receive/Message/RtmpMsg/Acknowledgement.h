#pragma once

#include "BaseMsg.h"

class CAcknowledgement : public CBaseMsg
{
public:
	CAcknowledgement(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CAcknowledgement();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};
