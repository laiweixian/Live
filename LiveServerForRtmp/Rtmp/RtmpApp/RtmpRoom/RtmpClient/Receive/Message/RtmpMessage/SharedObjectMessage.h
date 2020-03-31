#pragma once

#include "BaseMessage.h"

class CSharedObjectMessage : public CBaseMessage
{
public:
	CSharedObjectMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform);
	~CSharedObjectMessage();

	//CBaseMessage
	RtmpMessageType GetType();
	void Inform();
};
