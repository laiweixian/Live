#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "BaseMessage.h"


class CChunking 
{
protected:
	CChunking();
	~CChunking();
public:
	static CChunking* Create(CChunking* prev,CBaseMessage* curr,uint32_t chunkSize);
	void Destroy();

	uint8_t* GetChunksBuffer(uint32_t* outLength);
	struct Buff { uint8_t* buf; uint32_t length; };
	struct Chunk { Buff head; Buff payload; };

private:
	void Set(CChunking* prev, CBaseMessage* curr, uint32_t chunkSize);
	void SetChunkHead(CChunking* prev);
	void SetChunkPayload(CBaseMessage* curr, uint32_t chunkSize);
	void SetFirstChunkHead(CChunking* prev);
	void SetOtherChunkHead();
	uint32_t GetNextCsid();

	
protected:
	vector<Chunk> m_Chunks;
	uint32_t m_DeltaTS;
	uint32_t m_Csid;
	CBaseMessage::Header m_MsgHeader;
};

