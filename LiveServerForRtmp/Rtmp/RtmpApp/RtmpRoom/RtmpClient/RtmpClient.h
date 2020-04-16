#pragma once

#include "Handles/Handles.h"

class CRtmpClient 
{
public:
	CRtmpClient(uint32_t chunkSize);
	~CRtmpClient();



private:
	CHandshake m_Handshake;
	CChunks	   m_Chunks;
};
