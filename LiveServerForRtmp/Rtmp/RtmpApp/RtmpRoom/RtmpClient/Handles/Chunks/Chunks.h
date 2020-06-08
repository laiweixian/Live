#pragma once

#include "ReceChunk/ReceChunk.h"
#include "SendChunk/SendChunk.h"

class CChunks : public CReceiveChunk , public CSendChunk
{
public:
	CChunks(const uint32_t chunkSize = 128);
	~CChunks();


protected:
	
	


private:
	uint32_t m_ChunkSize;

};
