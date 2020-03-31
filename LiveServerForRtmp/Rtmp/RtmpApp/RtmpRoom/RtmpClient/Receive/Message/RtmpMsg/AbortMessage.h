#pragma once

#include "BaseMsg.h"

class CAbortMessage : public CBaseMsg
{
public:
	CAbortMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CAbortMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};