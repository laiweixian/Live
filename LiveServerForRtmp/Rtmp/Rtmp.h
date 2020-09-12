#pragma once

#include "stdafx.h"

#include "Network/SocketIO.h"
#include "RtmpClients/ClientManager.h"

struct SockUser
{
	SOCKET_HANDLE handle;
	ISocketOperation *ioOp;
};

class CRtmp : public ISocketEvent , public IIOOperation
{
public:
	CRtmp();
	~CRtmp();
public:
	int Initialize();
	int Run();

protected:
	//ISocketEvent
	int OnConnect(SOCKET_HANDLE handle, ISocketOperation* iop);
	int OnDisConnect(SOCKET_HANDLE handle, ISocketOperation* iop) ;
	int OnReceive(SOCKET_HANDLE handle, ISocketOperation* iop);
	int OnSend(SOCKET_HANDLE handle, ISocketOperation* iop);
	int OnError(SOCKET_HANDLE handle, ISocketOperation* iop);

	//IIOOperation
	int WriteForHandle(const IO_HANDLE handle, uint8_t* buf, uint32_t length) ;
	int CloseForHandle(const IO_HANDLE handle) ;
	
private:
	CSocketIO *m_File;
	CClientManager *m_Client;
	vector<SockUser*> m_Users;

};