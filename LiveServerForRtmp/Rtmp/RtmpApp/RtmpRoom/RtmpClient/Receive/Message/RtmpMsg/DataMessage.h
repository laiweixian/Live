#pragma once

#include "BaseMsg.h"

class CDataMessage : public CBaseMsg
{
public:
	CDataMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CDataMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};