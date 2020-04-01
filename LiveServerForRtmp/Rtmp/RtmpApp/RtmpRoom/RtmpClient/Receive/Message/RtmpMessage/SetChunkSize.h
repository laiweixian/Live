#pragma once
#include "BaseMessage.h"

class CSetChunkSize : public CBaseMessage
{
public:
	CSetChunkSize(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSetChunkSize();

	//CBaseMessage
	RtmpMessageType GetType();
	void* GetPtr(int* outDstLen);
};