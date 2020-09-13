 #pragma once
#include "AntiChunking.h"

class CReceiveChunk
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	CAntiChunking* Receive(uint8_t* src, const int srcLength,int *outChunkLength);
	int Abort(uint32_t csid);

protected:
	virtual uint32_t GetChunkSize() = 0;
	
private:
	CAntiChunking *m_Lastest;
};
