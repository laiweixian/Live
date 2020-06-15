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

	enum State{NONE,WAIT_HANDSHAKE,WAIT_CHUNK,ERR};

	CSocketClient* GetClietnIo();

	void OnReceive();
	void OnDisConnct();
	void OnSockErr();
	
protected:
	int Send2Peer( uint8_t* src, const int srcLength);
private:
	void UpdateReadBuff();
private:
	CSocketClient *m_IO;
	State m_State;

	CBuffer m_Readable;
};
