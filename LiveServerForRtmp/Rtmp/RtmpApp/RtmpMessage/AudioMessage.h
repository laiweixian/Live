#pragma once

#include "BaseMessage.h"

#define DECLARE_AUDIO_MESSAGE	\
	struct Content{uint32_t buffSize;uint8_t* buff;};

/*-----------------------------------------------------------------------------------------*/
class CAudioMessage : public CBaseMessage
{
public:
	DECLARE_AUDIO_MESSAGE
	CAudioMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CAudioMessage();

	//CBaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CAudioMessage::Content* GetContent();
	static void Content_free(CAudioMessage::Content** ppContent);
};