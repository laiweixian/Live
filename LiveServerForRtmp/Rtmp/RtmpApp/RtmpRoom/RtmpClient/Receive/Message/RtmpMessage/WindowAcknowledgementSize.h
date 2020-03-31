#pragma once

#include "BaseMessage.h"

class CWindowAcknowledgementSize : public CBaseMessage
{
public:
	CWindowAcknowledgementSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CWindowAcknowledgementSize();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};