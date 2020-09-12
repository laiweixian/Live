#pragma once

#include "stdafx.h"

#include "Network/SocketIO.h"
#include "RtmpClients/ClientManager.h"

class CRtmp : public ISocketEvent , public IClientOperation
{
public:
	CRtmp();
	~CRtmp();
public:
	int Initialize();
	int Run();

protected:
	//ISocketEvent
	int OnConnect(void* handle, ISocketOperation* iop);
	int OnDisConnect(void* handle, ISocketOperation* iop) ;
	int OnReceive(void* handle, ISocketOperation* iop);
	int OnSend(void* handle, ISocketOperation* iop);
	int OnError(void* handle, ISocketOperation* iop);

	//IClientOperation
	int WriteOperation(const void *pUser, uint8_t* buf, uint32_t length);
	int CloseOperation(const void *pUser, uint8_t* buf, uint32_t length);
	
private:
	CSocketIO *m_File;
	CClientManager *m_Client;
};