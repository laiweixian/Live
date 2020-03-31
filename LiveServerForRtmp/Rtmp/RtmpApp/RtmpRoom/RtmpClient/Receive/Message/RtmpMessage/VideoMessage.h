#pragma once

#include "BaseMessage.h"

class CVideoMessage : public CBaseMessage
{
public:
	CVideoMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CVideoMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};