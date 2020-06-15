#include "SocketIO.h"
#include "Rtmp/RtmpApp/RtmpClients/ClientManager.h"

#define DEFAULT_BUFF_LENGTH	1024

CSocketIO::CSocketIO(const char* ip, const int port, const int backlog , const int timeout , const int maxConnect):
		m_Event(NULL)
{
	strcpy_s(m_Optional.ip,ip);
	m_Optional.port = port;
	m_Optional.backlog = 0;
	m_Optional.maxConnect = 0;
	m_Optional.timeout = 0;
	
	m_ListSock = INVALID_SOCKET;

	InitListenSocket();
}

CSocketIO::~CSocketIO()
{

}

int CSocketIO::SetSocketNonblock(SOCKET sock)
{
	long sockCmd = FIONBIO;
	u_long arg = 0;
	return ioctlsocket(sock, sockCmd, &arg);
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

	// set socket non block
	ret = CSocketIO::SetSocketNonblock(listenSocket);
	if (ret == SOCKET_ERROR)
		goto sock_nonblock_err;

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
	auto it = m_Clients.begin();
	CSocketClient *client = NULL;
	int length = 0;

	for (it= m_Clients.begin(); it != m_Clients.end();it++)
	{
		client = *it;
		length = client->CheckRead();
		if (length > 0)
		{
			m_Event->Receive(client);
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
	CSocketClient *client = NULL;

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
		client = new CSocketClient(connSock,addr);
		m_Clients.push_back(client);
		m_Event->Connect(client);
	}

	return 0;
}



void CSocketIO::CloseServer()
{

}

void CSocketIO::RegisterEvent(ISocketEvent* event)
{
	m_Event = event;
}


