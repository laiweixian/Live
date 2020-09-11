#include "SocketIO.h"
#include "SocketClient.h"
#include "stdafx.h"

#define DEFAULT_BUFF_LENGTH	1024

struct SocketUser
{
	CSocketIO *pSock;
	CSocketClient *pClient;
};

CSocketIO::CSocketIO(const char* ip, const int port, const int backlog , const int timeout , const int maxConnect):m_Event(NULL)
{
	strcpy_s(m_Optional.ip,ip);
	m_Optional.port = port;
	m_Optional.backlog = 0;
	m_Optional.maxConnect = 0;
	m_Optional.timeout = 0;
	
	m_ListSock = INVALID_SOCKET;
}

CSocketIO::~CSocketIO()
{	
	auto it = m_Users.begin();
	SocketUser *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (SocketUser *)(*it);
		delete (pUser->pClient);
		pUser->pClient = NULL;
		pUser->pSock = NULL;

		delete (*it);
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
	SocketUser *pUser = NULL;
	int length = 0;
	SocketOperation call;

	call.close = CSocketIO::CloseS;
	call.read = CSocketIO::ReadS;
	call.write = CSocketIO::WriteS;

	for (it= m_Users.begin(); it != m_Users.end();it++)
	{
		pUser = (SocketUser*)*it;
		length = pUser->pClient->CheckRead();
		if (length > 0)
		{
			call.handle = *it;
			m_Event->ReadBuffEvent(&call);
		}
	}

	return 0;
}


int CSocketIO::CheckConnect()
{
	SOCKET connSock = INVALID_SOCKET;
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
	int errorCode;
	
	SocketOperation call;
	SocketUser *pUser = NULL;

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

		pUser = new SocketUser;
		pUser->pSock = this;
		pUser->pClient = new CSocketClient(connSock, addr);
		m_Users.push_back(pUser);

		call.handle = pUser;
		call.close = CSocketIO::CloseS;
		call.read = CSocketIO::ReadS;
		call.write = CSocketIO::WriteS;

		//通知用户
		if (m_Event)
			m_Event->ConnectEvent(&call);
	}

	return 0;
}



void CSocketIO::CloseServer()
{

}

void CSocketIO::RegisterEvent(IEvent* event)
{
	m_Event = event;
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

int CSocketIO::ReadS(void *SockHandle, uint8_t* buf, uint32_t bufSize)
{
	SocketUser *pUser = (SocketUser*)SockHandle;

	return pUser->pClient->Read(buf, bufSize);
}

int CSocketIO::WriteS(void *SockHandle, uint8_t* buf, uint32_t bufSize)
{
	SocketUser *pUser = (SocketUser*)SockHandle;

	return pUser->pClient->Write(buf, bufSize);
}

int CSocketIO::CloseS(void *SockHandle)
{
	SocketUser *pUser = (SocketUser*)SockHandle;
	return pUser->pClient->Close();
}


