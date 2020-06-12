#pragma once

#include "BaseMessage.h"

#define DECLARE_ABORT_MESSAGE	\
	struct Content{uint32_t chunkStreamID;};

/*-----------------------------------------------------------------------------------------*/
class CAbortMessage : public CBaseMessage
{
public:
	DECLARE_ABORT_MESSAGE
	CAbortMessage(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAbortMessage();

	//BaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CAbortMessage::Content GetContent();
private:
	CAbortMessage::Content m_Content;
};