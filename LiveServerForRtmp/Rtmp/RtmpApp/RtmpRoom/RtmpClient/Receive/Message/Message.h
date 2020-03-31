#pragma once

#include "../Receiver.h"
#include "Chunk/Chunk.h"
#include "RtmpMsg/RtmpMessage.h"

#define CHUNK_SIZE 128

class CMessage : public CReciever
{
public:
	CMessage(IOutStream* pOut);
	~CMessage();

	//CReciever
	int OnReceive( void* src, const int srcLength);
private:
	int ParseChunk(void* src, const int srcLength);

private:
	CChunkHeader *m_PrevHeader;
	CBaseMessage *m_Msg;

	uint32_t m_ChunkSize;
};
