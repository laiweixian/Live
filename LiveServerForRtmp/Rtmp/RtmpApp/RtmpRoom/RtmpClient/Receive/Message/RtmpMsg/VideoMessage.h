#pragma once

#include "BaseMsg.h"

class CVideoMessage : public CBaseMsg
{
public:
	CVideoMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CVideoMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};