#pragma once

#include "BaseMessage.h"

#define DECLARE_ACKNOWLEDGEMENT	\
	struct Content{uint32_t sequenceNumber;};

/*-----------------------------------------------------------------------------------------*/
class CAcknowledgement : public CBaseMessage
{
public:
	DECLARE_ACKNOWLEDGEMENT
	CAcknowledgement(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAcknowledgement();

	//CBaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CAcknowledgement::Content GetContent();
private:
	CAcknowledgement::Content m_Content;
};
