#pragma once

#include "Receive/ReceiveChunk.h"
#include "HandleMessage.h"

class CChunks : public CReceiveChunk,
				public CHandleMessage
{
protected:
	CChunks(uint32_t chunkSize);
	virtual ~CChunks();

protected:
	int OnChunks(uint8_t* src, const int srcLength);

private:
	uint32_t GetChunkSize();

private:
	int AbortMessageHandle(uint32_t csid);
	int SetChunkSizeHandle(uint32_t chunkSize);
	uint32_t m_ChunkSize;
};
