#pragma once

#include "BaseMsg.h"

class CUserControlMessages : public CBaseMsg
{
public:
	CUserControlMessages(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CUserControlMessages();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};