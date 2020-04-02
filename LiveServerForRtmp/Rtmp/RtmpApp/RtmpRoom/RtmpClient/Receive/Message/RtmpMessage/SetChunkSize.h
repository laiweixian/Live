#pragma once
#include "BaseMessage.h"

class CSetChunkSize : public CBaseMessage
{
public:
	CSetChunkSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSetChunkSize();

	//property
	uint32_t GetChunkSize() = 0;

	//CBaseMessage
	RtmpMessageType GetType();
};