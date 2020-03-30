#pragma once

#include "../Receive.h"
#include "Chunk/Chunk.h"

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
};
