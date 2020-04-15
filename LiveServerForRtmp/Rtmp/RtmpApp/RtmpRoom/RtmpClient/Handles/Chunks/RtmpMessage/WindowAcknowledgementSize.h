#pragma once

#include "BaseMessage.h"

#define DECLARE_WINDOW_ACKNOWLEDGEMENT_SIZE	\
	struct Content{uint32_t acknowledgementWindowSize;};

/*-----------------------------------------------------------------------------------------*/
class CWindowAcknowledgementSize : public CBaseMessage
{
public:
	DECLARE_WINDOW_ACKNOWLEDGEMENT_SIZE
	CWindowAcknowledgementSize(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CWindowAcknowledgementSize();

	//CBaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CWindowAcknowledgementSize::Content GetContent();
private:
	CWindowAcknowledgementSize::Content m_Content;
	
}; 