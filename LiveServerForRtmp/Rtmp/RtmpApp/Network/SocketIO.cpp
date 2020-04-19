#include "SocketIO.h"

#define DEFAULT_BUFF_LENGTH	1024


ISocket::ISocket(ISocketEvent *pEvent) : m_Event(pEvent)
{

}

ISocket::~ISocket()
{

}

CSocketIO::CSocketIO(ISocketEvent *pEvent) : ISocket(pEvent), m_ListSock(INVALID_SOCKET)
{

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

int CSocketIO::Open(ISocket::Optional opti)
{
	WSADATA wsa;
	int ret ;
	ULONG ret;
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
	service.sin_port = htons(opti.port);
	service.sin_addr.s_addr = inet_addr(opti.ip);
	ret = bind(listenSocket, (sockaddr*)&service, sizeof(service));
	if (ret == SOCKET_ERROR)
		goto sock_bind_err;

	//set listen backlog
	ret = listen(listenSocket, opti.backlog);
	if (ret == SOCKET_ERROR)
		goto sock_listen_err;

	m_ListSock = listenSocket;
	m_Optional = opti;

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

int CSocketIO::Read(const int ioID, const void *src, size_t srcSize,int *outSize)
{
	auto it = m_Connecters.begin();
	Connecter *pConn = NULL;
	int readLen = 0;

	for (it = m_Connecters.begin(); it != m_Connecters.end(); it++)
	{
		if ((*it)->ioid == ioID)
			pConn = *it;
	}
		
	if (pConn == NULL)
		return ERROR_SOCK_NO_EXIST;


	
	return SOCKET_OK;
}

int CSocketIO::Write(const int ioID, const void *src, size_t srcSize, int *outSize)
{
	auto it = m_Connecters.begin();
	Connecter *pConn = NULL;

	for (it = m_Connecters.begin(); it != m_Connecters.end(); it++)
	{
		if ((*it)->ioid == ioID)
			pConn = *it;
	}

	if (pConn == NULL)
		return ERROR_SOCK_NO_EXIST;

	return SOCKET_OK;
}

int CSocketIO::Close(const int ioID)
{

}

void CSocketIO::Loop()
{
	CheckConnect();
	CheckReceive();
}

int CSocketIO::CheckConnect()
{
	SOCKET connSock = INVALID_SOCKET;
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
	int errorCode;
	Connecter *conn = NULL;
	vector<int> newIds;
	auto it = newIds.begin();

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
		CSocketIO::SetSocketNonblock(connSock);

		conn = new Connecter;
		conn->ioid = GenIOID();
		conn->sock = connSock;
		conn->addr = addr;
		conn->cType = ConnType::ONLINE;
		conn->buff = new uint8_t[DEFAULT_BUFF_LENGTH];
		conn->buffLen = DEFAULT_BUFF_LENGTH;
		conn->length = 0;
		m_Connecters.push_back(conn);
		newIds.push_back(conn->ioid);
	}

	//inform 
	for (it = newIds.begin(); it != newIds.end(); it++)
		m_Event->OnConnect(*it);
	return 0;
}

int CSocketIO::CheckReceive()
{
	auto it = m_Connecters.begin();
	int errorCode;
	Connecter *pConn = NULL;
	int remainSize = 0;
	uint8_t *ptr = NULL;
	int length = 0;

	vector<int> closeInfos;
	vector<int> recvInfos;
	vector<int>::iterator it;

	for (it=m_Connecters.begin();it!= m_Connecters.end();it++)
	{
		pConn = *it;
		remainSize = pConn->buffLen - pConn->length;
		if (remainSize <= 0)
			continue;
		ptr = pConn->buff + pConn->length;
		length = ::recv(pConn->sock, (char*)ptr,remainSize,0);
		if (length == 0)
		{
			pConn->cType = OUTLINE;
			m_Event->OnClose(pConn->ioid);
		}
		else if (length > 0)
		{
			pConn->length += length;
			m_Event->OnReceive(pConn->ioid);
		}
		else
		{
			errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
				continue;
			else{
				pConn->cType = CSocketIO::ConnType::ERR;
				m_Event->OnError(pConn->ioid, errorCode);
			}
		}
	}
}