#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"


class CRtmpClient 
{
private:
	CRtmpClient(int id,uint32_t chunkSize);
	~CRtmpClient();

public:
	static CRtmpClient* Create(const int id,const uint32_t chunkSize = 128);
	void Destroy();

	int Handle(uint8_t *src, const int srcLen) ;
private:
	CHandshake m_Handshake;
	CChunks	   m_Chunks;
};
