#pragma once

#include "../Receive.h"
#include "Chunk/Chunk.h"
#include "RtmpMsg/RtmpMsg.h"

#define CHUNK_SIZE 128

class CMessage : public IReceive
{
public:
	CMessage(SendToPeer sendToPeer);
	~CMessage();

	//IReceive
	int OnReceive( void* src, const int srcLength);
private:
	int ParseChunk(void* src, const int srcLength);

private:
	CChunkHeader *m_PrevHeader;
	CBasem *m_Msg;

	uint32_t m_ChunkSize;
};
