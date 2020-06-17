#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"
#include "Buffer.h"

class CSocketClient;

class CRtmpClient : public CHandshake,\
					public CChunks
{
public:


	CRtmpClient(string appName, uint32_t chunkSize, CSocketClient *io);
	~CRtmpClient();

	CSocketClient* GetClietnIo();

	void OnReceive();
	void OnDisConnct();
	void OnSockErr();
	
protected:
	int Send2Peer( uint8_t* src, const int srcLength);

private:

private:
	CSocketClient *m_IO;

	CBuffer m_Buf;
};
