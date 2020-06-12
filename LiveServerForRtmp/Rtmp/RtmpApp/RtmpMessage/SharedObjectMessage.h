#pragma once

#include "BaseMessage.h"

/*-----------------------------------------------------------------------------------------*/
class CSharedObjectMessage : public CBaseMessage
{
public:
	CSharedObjectMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSharedObjectMessage();

	//CBaseMessage
	CBaseMessage::MessageType GetType();
	
};
