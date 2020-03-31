#pragma once

#include "BaseMessage.h"

class CDataMessage : public CBaseMessage
{
public:
	CDataMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CDataMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};