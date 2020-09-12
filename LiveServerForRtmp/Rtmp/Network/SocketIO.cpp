#include "SocketIO.h"
#include "SocketClient.h"
#include "stdafx.h"

#define DEFAULT_BUFF_LENGTH	1024



CSocketIO::CSocketIO(ISocketEvent *pEvent,const char* ip, const int port, const int backlog , const int timeout , const int maxConnect):m_Event(NULL)
{
	strcpy_s(m_Optional.ip,ip);
	m_Optional.port = port;
	m_Optional.backlog = 0;
	m_Optional.maxConnect = 0;
	m_Optional.timeout = 0;
	
	m_ListSock = INVALID_SOCKET;

	m_Event = pEvent;
}

CSocketIO::~CSocketIO()
{	
	auto it = m_Users.begin();
	CSocketClient *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (CSocketClient *)(*it);
		delete (pUser);
		*it = NULL;
	}
	m_Users.clear();

	closesocket(m_ListSock);
}



int CSocketIO::SetSocketNonblock(SOCKET sock)
{
	int imode = 1;
	return ioctlsocket(sock, FIONBIO, (u_long *)&imode);
}

int CSocketIO::InitListenSocket()
{
	WSADATA wsa;
	int ret ;
	SOCKET listenSocket = INVALID_SOCKET;
	sockaddr_in service;

	//initialize winsock
	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != NO_ERROR)
		goto sock_init_err;

	//create socket
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
		goto sock_create_err;

	//bind socket
	service.sin_family = AF_INET;
	service.sin_port = htons(m_Optional.port);
	service.sin_addr.s_addr = inet_addr(m_Optional.ip);
	
	ret = bind(listenSocket, (sockaddr*)&service, sizeof(service));
	if (ret == SOCKET_ERROR)
		goto sock_bind_err;

	//set listen backlog
	ret = listen(listenSocket, m_Optional.backlog);
	if (ret == SOCKET_ERROR)
		goto sock_listen_err;

	// set socket non block
	ret = CSocketIO::SetSocketNonblock(listenSocket);
	if (ret == SOCKET_ERROR)
		goto sock_nonblock_err;

	m_ListSock = listenSocket;
	return SOCKET_OK;

sock_init_err:
	WSACleanup();
	return ERROR_SOCK_INIT;
sock_create_err:
	WSACleanup();
	closesocket(listenSocket);
	return ERROR_SOCK_CREATE;
sock_nonblock_err:
	WSACleanup();
	closesocket(listenSocket);
	return ERROR_SOCK_NON_BLOCAK;
sock_bind_err:
	WSACleanup();
	closesocket(listenSocket);
	return ERROR_SOCK_BIND;
sock_listen_err:
	WSACleanup();
	closesocket(listenSocket);
	return ERROR_SOCK_LISTEN;
}

int CSocketIO::CheckEvent()
{
	CheckConnect();
	CheckReceive();
	return 0;
}

int CSocketIO::CheckReceive()
{
	auto it = m_Users.begin();
	CSocketClient *pUser = NULL;
	int length = 0;
	

	for (it= m_Users.begin(); it != m_Users.end();it++)
	{
		pUser = (CSocketClient*)*it;
		length = pUser->CheckRead();
		if (length > 0)
			m_Event->OnReceive(pUser, this);
	}
	return 0;
}


int CSocketIO::CheckConnect()
{
	SOCKET connSock = INVALID_SOCKET;
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
	int errorCode;
	CSocketClient *pUser = NULL;

	connSock = accept(m_ListSock, (sockaddr*)&addr, &len);
	if (connSock == INVALID_SOCKET)
	{
		errorCode = WSAGetLastError();
		if (errorCode != WSAEWOULDBLOCK)
		{
			CloseServer();
			return -1;
		}
	}
	else
	{
		SetSocketNonblock(connSock);
		pUser = new CSocketClient(connSock, addr);
		m_Users.push_back(pUser);

		//通知用户
		if (m_Event)
			m_Event->OnConnect(pUser,this);
	}

	return 0;
}





int CSocketIO::Initialize()
{
	InitListenSocket();
	return 0;
}

int CSocketIO::Run()
{
	return CheckEvent();
}

int CSocketIO::Read(void* handle, uint8_t* buf, uint32_t length)
{
	CSocketClient *pUser = (CSocketClient*)handle;
	return pUser->Read(buf, length);
}

int CSocketIO::Write(void* handle, uint8_t* buf, uint32_t length)
{
	CSocketClient *pUser = (CSocketClient*)handle;
	return pUser->Write(buf, length);
}

int CSocketIO::Close(void* handle)
{
	CSocketClient *pUser = (CSocketClient*)handle;
	return pUser->Close();
}


