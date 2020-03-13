#pragma once

#include "../../stdafx.h"
#include "../../CoreModule.h"
#include "../IOModule.h"
#include <WinSock2.h>




#define DEFAULT_MAX_CONN	100
#define DEFAULT_TIME_OUT	500
#define DEFAULT_BACK_LOG	100

#define SOCKET_INIT_ERR -1
#define SOCKET_CREATE_ERR -2
#define SOCKET_SET_CMD_ERROR -3
#define SOCKET_BIND_ERR -4
#define SOCKET_LISTEN_ERR -5
#define NO_LISTEN_SOCKET -6

#define CORE_IO_NAME	"socket"

enum DispatchType
{
	CONNECT,READ,WRITE,CLOSE,IO_ERR
};

struct Connecter
{
	int ioid;
	SOCKET sockfd;
	char*	ip;

	char receiveBuff[1024];
	int	 receiveBuffLen;
};



class CSocketIO :	public IIO 
{
public:
	CSocketIO();
	~CSocketIO();



	//IIO
	int Open() ;
	int Read(const int ioId, char *buff, const int buffLen) ;
	int Write(const int ioId, char *buff, const int buffLen) ;
	int Close(const int ioId);

	//property
	char* GetIp();
	int GetPort();

	ULONG ThreadHandle();

private:
	
	ULONG InitSocket();
	static int SetSocketNonblock(SOCKET sock);
	
	//
	int CheckAccept();
	int CheckReceive();
	int Dispatch(DispatchType dType, const int ioId);
private:
	char m_Ip[100];
	int  m_Port;
	int  m_MaxConnect;
	int  m_TimeOut;
	int  m_Backlog;
	IIOMsg *m_Msg;

	int		m_ConnectIndex;
	SOCKET m_ListenFd;
	vector<Connecter*> m_Connects;

};