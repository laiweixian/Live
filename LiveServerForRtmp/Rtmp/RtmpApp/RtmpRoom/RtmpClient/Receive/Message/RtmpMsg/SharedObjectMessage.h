#pragma once

#include "BaseMsg.h"

class CSharedObjectMessage : public CBaseMsg
{
public:
	CSharedObjectMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform);
	~CSharedObjectMessage();

	//CBaseMsg
	RtmpMessageType GetType();
	void Inform();
};
