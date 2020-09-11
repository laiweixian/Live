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

class CSocketIO 
{
protected:
	DECLARE_SOCKET_OPT
	CSocketIO(const char* ip,const int port,const int backlog = 0,const int timeout = 0,const int maxConnect = 0);
	virtual ~CSocketIO();
public:
	void RegisterEvent(IEvent *pEvent);

protected:
	int Initialize();
	int Run();
public:
	static int ReadS(void *SockHandle, uint8_t* buf, uint32_t bufSize);
	static int WriteS(void *SockHandle, uint8_t* buf, uint32_t bufSize);
	static int CloseS(void *SockHandle);
private:
	int InitListenSocket();
	int CheckEvent();
	void CloseServer();

	static int SetSocketNonblock(SOCKET sock);
	
	
	int CheckConnect();
	int CheckReceive();

private:
	
	Optional m_Optional;
	SOCKET m_ListSock;

	IEvent *m_Event;
	vector<void*> m_Users;
};
