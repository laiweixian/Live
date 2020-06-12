#pragma once
#include "BaseMessage.h"

#define DECLARE_SET_CHUNK_SIZE	struct Content{ uint32_t  chunkSize;};
	
/*-----------------------------------------------------------------------------------------*/
class CSetChunkSize : public CBaseMessage
{
public:
	DECLARE_SET_CHUNK_SIZE
	CSetChunkSize(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSetChunkSize();

	//CBaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CSetChunkSize::Content GetContent();
private:
	CSetChunkSize::Content m_Content;
};