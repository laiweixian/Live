#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "BaseM.h"

class CAntiChunking : public CBaseM
{
private:
	CAntiChunking(uint32_t chunkSize);
	~CAntiChunking();
public:
	static CAntiChunking* Create(CAntiChunking* prev, uint32_t chunkSize, uint8_t* chunkBuf, const uint32_t chunkBufLen, int *outLength);
	void Destroy();
	int AppendChunk(uint8_t* chunkBuf, const uint32_t chunkBufLen);
	bool Legal();
	
private:
	void SetFirstChunk(CChunkHeader* pHead, uint8_t *data, int dataLen);
protected:
	CChunkHeader* m_Header;
	uint32_t m_ChunkSize;
};

