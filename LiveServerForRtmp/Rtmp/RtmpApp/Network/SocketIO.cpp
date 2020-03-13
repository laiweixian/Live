#include "SocketIO.h"

CSocketIO::CSocketIO()
{
	
}

CSocketIO::~CSocketIO()
{

}








char* CSocketIO::GetIp()
{
	return m_Ip;
}

int CSocketIO::GetPort()
{
	return m_Port;
}

int CSocketIO::Open()
{
	return InitSocket();
}

int CSocketIO::Read(const int ioId, char *buff, const int buffLen)
{
	Connecter *conn = NULL;
	auto it = m_Connects.begin();
	SOCKET fd = INVALID_SOCKET;
	int readLen = 0,remainLen = 0;
	char *temp0 = NULL,*temp1 = NULL;

	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		conn = *it;
		if (conn->ioid == ioId)
			fd = conn->sockfd;
	}

	if (fd == INVALID_SOCKET)
		return 0;

	//
	if (buffLen >= conn->receiveBuffLen)
	{
		readLen = conn->receiveBuffLen;
		memcpy(buff, conn->receiveBuff, readLen);
		memset(conn->receiveBuff, 0, readLen);
		conn->receiveBuffLen = 0;
	}
	else
	{
		readLen = buffLen;
		temp0 = new char[readLen];
		memcpy(temp0,conn->receiveBuff,readLen);
		
		remainLen = conn->receiveBuffLen - readLen;
		temp1 = new char[remainLen];
		memcpy(temp1, conn->receiveBuff + readLen , remainLen);

		memset(conn->receiveBuff,0, conn->receiveBuffLen);
		memcpy(conn->receiveBuff,temp1,remainLen);
		conn->receiveBuffLen = remainLen;
	
		memcpy(buff,temp0,readLen);
		delete[] temp0 ; delete[] temp1;
	}

	return readLen;
}

int CSocketIO::Write(const int ioId, char *buff, const int buffLen)
{
	Connecter *temp = NULL;
	auto it = m_Connects.begin();
	SOCKET fd = INVALID_SOCKET;
	int writeLen = 0;

	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->ioid == ioId)
			fd = temp->sockfd;
	}

	if (fd == INVALID_SOCKET)
		return 0;

	writeLen = send(fd, buff, buffLen, 0);
	return writeLen;
}

int CSocketIO::Close(const int ioId)
{
	Connecter *temp = NULL;
	auto it = m_Connects.begin();
	SOCKET fd = INVALID_SOCKET;

	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->ioid == ioId)
			fd = temp->sockfd;
	}

	if (fd == INVALID_SOCKET)
		return 0;

	return closesocket(fd);
}

ULONG CSocketIO::InitSocket()
{
	//initialize winsock
	WSADATA wsa;
	int iResult;
	ULONG ret;
	SOCKET listenSocket = INVALID_SOCKET;
	sockaddr_in service;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != NO_ERROR)
		goto sock_init_err;

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
		goto sock_create_err;
	m_ListenFd = listenSocket;

	//set listen fd nonblocking
	iResult = SetSocketNonblock(listenSocket);
	if (iResult == SOCKET_ERROR)
		goto sock_cmd_err;

	//ready ip address and port 
	service.sin_family = AF_INET;
	service.sin_port = htons(m_Port);
	service.sin_addr.s_addr = inet_addr(m_Ip);
	iResult = bind(listenSocket, (sockaddr*)&service, sizeof(service));
	if (iResult == SOCKET_ERROR)
		goto sock_bind_err;

	iResult = listen(listenSocket, m_Backlog);
	if (iResult == SOCKET_ERROR)
		goto sock_listen_err;

	return SAR_OK;
	//
sock_init_err:
	WSACleanup();
	return SOCKET_INIT_ERR;

sock_create_err:
	WSACleanup();
	closesocket(listenSocket);
	m_ListenFd = INVALID_SOCKET;
	return SOCKET_CREATE_ERR;

sock_cmd_err:
	WSACleanup();
	closesocket(listenSocket);
	m_ListenFd = INVALID_SOCKET;
	return SOCKET_SET_CMD_ERROR;

sock_bind_err:
	WSACleanup();
	closesocket(listenSocket);
	m_ListenFd = INVALID_SOCKET;
	return SOCKET_BIND_ERR;

sock_listen_err:
	WSACleanup();
	closesocket(listenSocket);
	m_ListenFd = INVALID_SOCKET;
	return SOCKET_LISTEN_ERR;
}

int CSocketIO::SetSocketNonblock(SOCKET sock)
{
	long sockCmd = FIONBIO;
	u_long arg = 0;
	return ioctlsocket(sock, sockCmd, &arg);
}

ULONG CSocketIO::ThreadHandle()
{
	int ret = 0;

	ret = CheckAccept();
	ret = CheckReceive();


	return 0;
}

int CSocketIO::CheckAccept()
{
	SOCKET userSock = INVALID_SOCKET;
	sockaddr_in userAddr;
	int len = sizeof(userAddr);
	char* userIp = NULL;
	int errorCode;
	Connecter *conn = NULL;

	if (m_ListenFd == INVALID_SOCKET)
		return NO_LISTEN_SOCKET;

	userSock = accept(m_ListenFd, (sockaddr*)&userAddr, &len);
	if (userSock == INVALID_SOCKET)
	{
		errorCode = WSAGetLastError();
		if (errorCode != WSAEWOULDBLOCK)
		{
			WSACleanup();
			closesocket(m_ListenFd);
			m_ListenFd = INVALID_SOCKET;
		}
	}
	else
	{
		CSocketIO::SetSocketNonblock(userSock);
		m_ConnectIndex++;
		userIp = inet_ntoa(userAddr.sin_addr);

		conn = new Connecter;
		memset(conn,0,sizeof(Connecter));
		strcpy(conn->ip, userIp);
		conn->sockfd = userSock;
		conn->ioid = m_ConnectIndex;
		m_Connects.push_back(conn);
		Dispatch(CONNECT, conn->ioid);
	}

	return 0;
}

int CSocketIO::CheckReceive()
{
	Connecter *conn = NULL;
	auto it = m_Connects.begin();
	int readLen = 0 , remainLen = 0;
	int errorCode = 0;

	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		conn = *it;
		remainLen = 1024 - conn->receiveBuffLen;
		if(remainLen <= 0)
			continue;
		readLen = recv(conn->sockfd,conn->receiveBuff+conn->receiveBuffLen,remainLen,0);
		if (readLen == 0)
		{
			Dispatch(CLOSE, conn->ioid);
		}
		else if (readLen > 0)
		{
			conn->receiveBuffLen += readLen;
			Dispatch(READ,conn->ioid);
		}
		else
		{
			errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
				continue;
			else
				Dispatch(IO_ERR,conn->ioid);
		}
	}

	return 0;
}

int CSocketIO::Dispatch(DispatchType dType,const int ioId)
{
	return 0;
}