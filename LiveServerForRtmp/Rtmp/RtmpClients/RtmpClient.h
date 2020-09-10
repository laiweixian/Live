#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"

#include "Buffer.h"

class CSocketClient;
class CInstanceManager;

class CRtmpClient : public CHandshake,\
					public CChunks
{
public:
	CRtmpClient(uint32_t chunkSize, CSocketClient *io,CInstanceManager* appInstance);
	~CRtmpClient();

	CSocketClient* GetClietnIo();

	void OnReceive();
	void OnDisConnct();
	void OnSockErr();
	
protected:
	int Send2Peer(uint8_t* src, const int srcLength);

private:
	CSocketClient *m_IO;
	CBuffer m_Read;
};
