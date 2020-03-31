#pragma once

#include "BaseMsg.h"

class CCommandMessage : public CBaseMsg
{
public:
	CCommandMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CCommandMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};