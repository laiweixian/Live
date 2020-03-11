#include "SocketIO/SocketIO.h"

CSocketIO::CSocketIO() :m_MaxConnect(DEFAULT_MAX_CONN),m_Port(DEFAULT_PORT), \
						m_TimeOut(DEFAULT_TIME_OUT), m_Backlog(DEFAULT_BACK_LOG), \
						m_ListenFd(INVALID_SOCKET),m_TatalConnect(0),\
						m_Message(NULL)
{
	strcpy(m_Ip, DEFAULT_IP);
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

ULONG CSocketIO::Open(const char* ip, const int port, CIOMessage* pMsg)
{
	strcpy(m_Ip, ip);
	m_Port = port;
	m_Message = pMsg;
	return InitSocket();
}

ULONG CSocketIO::Read(const int ioId,  char* buf, const int bufLen, int *outLen)
{
	Connecter *temp = NULL;
	int readLen = 0;
	int backBuffLen = 0;
	char backBuff[1024] = { 0 };
	auto it = m_Connects.begin();
	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->connId == ioId)
		{
			readLen = temp->buffLen > bufLen ? bufLen : temp->buffLen;
			if (readLen <= 0 )
				continue;
			
			memcpy(buf,temp->buff,readLen);
			*outLen = readLen;

			backBuffLen = temp->buffLen - readLen;
			if (backBuffLen > 0)
			{
				memcpy(backBuff,temp->buff+readLen,backBuffLen);
				memset(temp->buff,0,1024);
				memcpy(temp->buff, backBuff,backBuffLen);
			}
			return SAR_OK;
		}
	}

	return READ_ERR;
}

ULONG CSocketIO::Write(const int ioId,  char* buf, const int bufLen, int *outLen)
{
	Connecter *temp = NULL;
	auto it = m_Connects.begin();
	int len = 0,errorCode = 0;
	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->connId == ioId && temp->connectSock != INVALID_SOCKET)
		{
			len = send(temp->connectSock,buf,bufLen,0);
			if (len == 0)
			{
				return SAR_OK;
			}
			else if (len > 0)
			{
				//
				return SAR_OK;
			}
			else
			{
				errorCode = WSAGetLastError();
				if (errorCode == WSAEWOULDBLOCK)
				{
					//time out
					return WRITE_TIME_OUT;
				}
				else
				{
					
				}
			}
		}
	}

	return WRITE_ERR;
}

ULONG CSocketIO::Close(const int ioId)
{
	Connecter *temp = NULL;
	auto it = m_Connects.begin();
	int ret;

	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->connId == ioId)
		{
			ret = closesocket(temp->connectSock);
			m_Connects.erase(it);
			delete temp;

			return SAR_OK;
		}
	}
	return CLOSE_ERR;
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

ULONG CSocketIO::Run()
{
	SOCKET userSock = INVALID_SOCKET;
	sockaddr_in userAddr;
	int len = sizeof(userAddr);
	char* userIp = NULL;
	ULONG ret = SAR_OK;
	int errorCode;
	auto it = m_Connects.begin();
	int outLen = 0;
	Connecter *conn = NULL,*temp = NULL;
	
	if (m_ListenFd == INVALID_SOCKET)
		return NO_LISTEN_SOCKET;

	userSock = accept(m_ListenFd, (sockaddr*)&userAddr, &len);
	switch (userSock)
	{
	case INVALID_SOCKET:
		errorCode = WSAGetLastError();
		if (errorCode != WSAEWOULDBLOCK)
		{
			WSACleanup();
			closesocket(m_ListenFd);
			m_ListenFd = INVALID_SOCKET;
		}
		break;
	default:
		SetSocketNonblock(userSock);
		m_TatalConnect++;
		userIp = inet_ntoa(userAddr.sin_addr);

		conn = new Connecter;
		strcpy(conn->ip, userIp);
		conn->connectSock = userSock;
		conn->connId = m_TatalConnect;
		memset(conn->buff,0,1024);
		conn->buffLen = 0;
		conn->maxBuffLen = 1024;
		m_Connects.push_back(conn);
		break;
	}

	//check connect socket data
	for (it = m_Connects.begin(); it != m_Connects.end(); it++)
	{
		temp = *it;
		if (temp->buffLen >= temp->maxBuffLen)
		{
			//buff is full
			continue;
		}
		
		outLen = recv(temp->connectSock, temp->buff + temp->buffLen, temp->maxBuffLen - temp->maxBuffLen, 0);
		if (outLen == 0)
		{
			Close(temp->connId);
		}
		else if (outLen > 0)
		{
			temp->buffLen += outLen;
			m_Message->OnData(temp->connId);
		}
		else
		{
			errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
			{
				//time out
			}
			else
			{
				//connect socket error
				Close(temp->connId);
			}
		}
	}

	return ret;
}