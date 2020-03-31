#pragma once

#include "BaseMsg.h"

class CWindowAcknowledgementSize : public CBaseMsg
{
public:
	CWindowAcknowledgementSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CWindowAcknowledgementSize();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};