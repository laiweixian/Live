#pragma once

#include "BaseMessage.h"

/*-----------------------------------------------------------------------------------------*/
//����message�ļ��� ,����(abort message,video message,audio message, set chunk size message,and so on)
class CAggregateMessage : public CBaseMessage
{

public:
	CAggregateMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAggregateMessage();

	//CBaseMessage
	CBaseMessage::MessageType GetType();
	
};
