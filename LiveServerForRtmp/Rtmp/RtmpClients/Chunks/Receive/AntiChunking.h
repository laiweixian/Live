#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "BaseM.h"

class AntiChunking : public CBaseM
{
protected:
	AntiChunking(uint32_t chunkSize);
	virtual ~AntiChunking();
public:
	static AntiChunking* Create();
public:
	CChunkHeader* m_Header;
	uint32_t m_ChunkSize;
};

