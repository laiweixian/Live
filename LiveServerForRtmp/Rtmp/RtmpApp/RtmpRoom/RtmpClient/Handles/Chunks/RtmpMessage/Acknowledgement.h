#pragma once

#include "BaseMessage.h"

class CAcknowledgement : public CBaseMessage
{
public:
	CAcknowledgement(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAcknowledgement();

	//property
	int GetProperty(uint32_t* pSequenceNumber);

	//CBaseMessage
	RtmpMessageType GetType();
};
