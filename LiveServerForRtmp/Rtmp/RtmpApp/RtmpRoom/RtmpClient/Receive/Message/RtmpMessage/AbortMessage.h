#pragma once

#include "BaseMessage.h"

class CAbortMessage : public CBaseMessage
{
public:
	CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAbortMessage();

	uint32_t GetChunkStreamID();

	//BaseMessage
	RtmpMessageType GetType();
};