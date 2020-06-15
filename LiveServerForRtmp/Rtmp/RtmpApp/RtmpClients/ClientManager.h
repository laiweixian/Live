#pragma once

#include "RtmpClient.h"
#include "Rtmp/RtmpApp/Network/SockEvent.h"

class CSocketIO;

class CClientManager : private ISocketEvent
{
public:
	CClientManager();
	~CClientManager();

protected:
	int ClientManagerInit();
public:
	virtual int Connect(CSocketClient *pClient) final;
	virtual int DisConnect(CSocketClient *pClient)final;
	virtual int Receive(CSocketClient *pClient) final;
	virtual int SocketErr(CSocketClient *pClient) final;
	

	virtual string GetAppName() = 0;
	virtual uint32_t GetChunkSize() = 0;
	virtual CSocketIO*	GetSocketIO() = 0;
private:
	vector<CRtmpClient*> m_Clients;
};
