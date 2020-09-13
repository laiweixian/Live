#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "BaseMessage.h"

class CAntiChunking : public CBaseMessage
{
private:
	CAntiChunking(uint32_t chunkSize);
	~CAntiChunking();
public:
	static CAntiChunking* Create(CAntiChunking* prev, uint32_t chunkSize, uint8_t* chunkBuf, const uint32_t chunkBufLen, int *outLength);
	void Destroy();
	int AppendChunk(uint8_t* chunkBuf, const uint32_t chunkBufLen);
private:
	void SetFirstChunk(CChunkHeader* pHead, uint8_t *data, int dataLen);
protected:
	CChunkHeader* m_Header;
	uint32_t m_ChunkSize;
};

