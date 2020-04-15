#pragma once

#include "BaseMessage.h"

/*-----------------------------------------------------------------------------------------*/
class CDataMessage : public CBaseMessage
{
public:
	CDataMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CDataMessage();

	//CBaseMessage
	CBaseMessage::MessageType GetType();

};