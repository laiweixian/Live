#pragma once

#include "Receive/ReceiveChunk.h"
#include "Send/SendChunk.h"
#include "HandleMessage.h"

class CChunks : public CReceiveChunk,
				public CHandleMessage,
				public CSendChunk
{
protected:
	CChunks(uint32_t chunkSize);
	virtual ~CChunks();

protected:
	int OnChunks(uint8_t* src, const int srcLength);

private:
	uint32_t GetChunkSize();

	
private:
	 int AbortMessageHandle(CAbortMessage::Object *pObj) ;
	 int SetChunkSizeHandle(CSetChunkSize::Object *pObj) ;
	uint32_t m_ChunkSize;
};
