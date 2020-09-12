#pragma once

#include "stdafx.h"

#include "SockEvent.h"

#define SOCKET_OK	0	
#define ERROR_SOCK_INIT				-1
#define ERROR_SOCK_CREATE			-2
#define ERROR_SOCK_NON_BLOCAK		-3
#define ERROR_SOCK_BIND				-4
#define ERROR_SOCK_LISTEN			-5	
#define ERROR_SOCK_NO_EXIST			-6


#define DECLARE_SOCKET_OPT	\
		struct Optional{		\
			char ip[100];		\
			int port;			\
			int backlog;		\
			int timeout;		\
			int maxConnect;};

class CSocketIO : public ISocketOperation
{
public:
	DECLARE_SOCKET_OPT
	CSocketIO(ISocketEvent *pEvent,const char* ip,const int port,const int backlog = 0,const int timeout = 0,const int maxConnect = 0);
	~CSocketIO();

	int Initialize();
	int Run();
public:
	int Read(SOCKET_HANDLE handle,uint8_t* buf, uint32_t length) ;
	int Write(SOCKET_HANDLE handle,uint8_t* buf, uint32_t length) ;
	int Close(SOCKET_HANDLE handle);
private:
	int InitListenSocket();
	int CheckEvent();


	static int SetSocketNonblock(SOCKET sock);
	int CheckConnect();
	int CheckReceive();
private:
	Optional m_Optional;
	SOCKET m_ListSock;
	ISocketEvent *m_Event;
	vector<SOCKET_HANDLE> m_Users;
};
