#pragma once

#include "BaseMessage.h"

class CWindowAcknowledgementSize : public CBaseMessage
{
public:
	CWindowAcknowledgementSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CWindowAcknowledgementSize();

	//property
	uint32_t GetAcknowledgementWindowSize();

	//CBaseMessage
	RtmpMessageType GetType();
	
}; 