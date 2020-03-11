#pragma once

#include "stdafx.h"
#include <WinSock2.h>
#include "SocketIO/IOBase.h"

#define DEFAULT_IP			"0.0.0.0"
#define DEFAULT_PORT		0
#define DEFAULT_MAX_CONN	100
#define DEFAULT_TIME_OUT	500
#define DEFAULT_BACK_LOG	100

struct Connecter
{
	int  connId;
	SOCKET connectSock;
	char ip[100];
	char buff[1024];
	int buffLen;
	int maxBuffLen;
};

class CSocketIO : public CIOInterface
{
public:
	CSocketIO();
	~CSocketIO();

	//CIOInterface
	ULONG Open(const char* ip, const int port, CIOMessage* pMsg);
	ULONG Read(const int ioId,  char* buf, const int bufLen, int *outLen) ;
	ULONG Write(const int ioId,  char* buf, const int bufLen, int *outLen);
	ULONG Close(const int ioId) ;

	//property
	char* GetIp();
	int GetPort();

	ULONG Run();

private:
	
	ULONG InitSocket();
	int SetSocketNonblock(SOCKET sock);
private:
	char m_Ip[100];
	int  m_Port;
	int  m_MaxConnect;
	int  m_TimeOut;
	int  m_Backlog;

	CIOMessage *m_Message;
	SOCKET m_ListenFd;
	vector<Connecter*> m_Connects;

	//
	int m_TatalConnect;
};