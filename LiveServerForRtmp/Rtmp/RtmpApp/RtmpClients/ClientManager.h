#pragma once

#include "RtmpClient.h"
#include "Rtmp/RtmpApp/Network/SockEvent.h"

class CSocketIO;

class CClientManager : private ISocketEvent
{
public:
	CClientManager(uint32_t chunkSize);
	~CClientManager();

protected:
	int PreInitialize();
	int Initialize();
	int Run();
	int Pause();
	int Stop();

public:
	virtual int Connect(CSocketClient *pClient) final;
	virtual int DisConnect(CSocketClient *pClient)final;
	virtual int Receive(CSocketClient *pClient) final;
	virtual int SocketErr(CSocketClient *pClient) final;
protected:
	virtual CSocketIO*			GetSocketIO() = 0;
	virtual CInstanceManager*	GetInstanceManager() = 0;
private:
	uint32_t m_ChunkSize;
	vector<CRtmpClient*> m_Clients;
};
