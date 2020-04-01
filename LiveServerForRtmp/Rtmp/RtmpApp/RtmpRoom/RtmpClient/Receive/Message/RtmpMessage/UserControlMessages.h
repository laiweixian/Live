#pragma once

#include "BaseMessage.h"

class CUserControlMessages : public CBaseMessage
{
public:
	CUserControlMessages(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CUserControlMessages();

	//CBaseMessage
	RtmpMessageType GetType();
	void* GetPtr(int* outDstLen);
};