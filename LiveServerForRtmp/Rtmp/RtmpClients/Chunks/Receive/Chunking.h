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

	uint8_t* Encode(uint32_t* outLength);
	struct Buff { uint8_t* buf; uint32_t length; };
	struct Chunk { Buff head; Buff payload; };

protected:
	void Set(CChunking* prev, CBaseMessage* curr, uint32_t chunkSize);
	void Encode(CBaseMessage* curr,const uint32_t chunkSize);
private:
	uint8_t CheckFirstHeader(CChunking* prev, CBaseMessage* curr);
	void SetFirstChunk(CChunking* prev, CBaseMessage* curr);
	void SetFirstChunk0(CChunking* prev, CBaseMessage* curr);
	void SetFirstChunk1(CChunking* prev, CBaseMessage* curr);
	void SetFirstChunk2(CChunking* prev, CBaseMessage* curr);
	void SetFirstChunk3(CChunking* prev, CBaseMessage* curr);
	void SetChunk4(uint32_t count);
	
protected:
	vector<CChunkHeader::Head> m_ChunkHeads;
	CBaseMessage::Header m_MsgHeader;
	
	vector<Chunk> m_Chunks;

};

