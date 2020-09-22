 #pragma once
#include "AntiChunking.h"

class CReceiveChunk
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	CBaseMessage* Receive(uint8_t* src, const int srcLength,int *outChunkLength);
	int Abort(uint32_t csid);
	int ChangeChunkSize(uint32_t chunkSize);

protected:
	
	
private:
	CAntiChunking *m_Lastest;
	uint32_t m_ReceiveChunkSize;
};
