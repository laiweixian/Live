#pragma once

#include "Handshake/Handshake.h"
#include "Chunks/Chunks.h"
#include "Buffer.h"

class CRtmpClient;
class CClientManager;

class CRtmpClient : public CHandshake,\
					public CChunks
{
public:
	CRtmpClient(uint32_t chunkSize,CClientManager* pManager);
	~CRtmpClient();

public:
	void Processing(uint8_t *buf,int bufLen);
	
private:
	void Processing();

protected:
	int Send2Peer(uint8_t* src, const int srcLength);

private:
	CBuffer m_Read;
	CClientManager *m_Manager;
};
