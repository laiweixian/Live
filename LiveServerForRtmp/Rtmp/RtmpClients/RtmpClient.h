#pragma once

#include "Handshake/Handshake.h"
#include "Chunks/Chunks.h"
#include "../Network/SockEvent.h"


#include "Buffer.h"

class CRtmpClient;


class CRtmpClient : public CHandshake,\
					public CChunks
{
public:
	CRtmpClient(uint32_t chunkSize);
	~CRtmpClient();

public:
	void Processing(uint8_t *buf,int bufLen,int *outLength);
	
/*
	void OnReceive();
	void OnDisConnct();
	void OnSockErr();
*/
protected:
	int Send2Peer(uint8_t* src, const int srcLength);

private:
	CBuffer m_Read;
};
