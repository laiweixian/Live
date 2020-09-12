#pragma once

#include "stdafx.h"

#include "Network/SocketIO.h"
#include "RtmpClients/ClientManager.h"

class CRtmp : public ISocketEvent  
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
	int OnErr(void* handle, ISocketOperation* iop);
	
private:
	CSocketIO *m_File;
	CClientManager *m_Client;
};