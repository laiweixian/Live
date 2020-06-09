#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"



class CRtmpClient : public CHandshake,\
					public CChunks,\
			
				

{
public:
	static CRtmpClient* Create(const int id, const uint32_t chunkSize = 128);
	void Destroy();
	
private:
	CRtmpClient(int id,uint32_t chunkSize);
	~CRtmpClient();

private:
	//
	int Send2Peer(const uint8_t* src, const int srcLength);
	
};
