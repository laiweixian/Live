#pragma once

#include "BaseMessage.h"
#include "AMF/AMF.h"

class CCommandMessage : public CBaseMessage
{
public:
	CCommandMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CCommandMessage();

	//CBaseMessage
	RtmpMessageType GetType();

};