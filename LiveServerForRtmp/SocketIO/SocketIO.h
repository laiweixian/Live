#pragma once

#include "../stdafx.h"
#include <WinSock2.h>
#include "IOBase.h"


#define DEFAULT_MAX_CONN	100
#define DEFAULT_TIME_OUT	500
#define DEFAULT_BACK_LOG	100

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



class CSocketIO : public IIO
{
public:
	CSocketIO(IIOMsg* pMsg,const char* ip,const int port,int maxConnect = DEFAULT_MAX_CONN,int timeout = DEFAULT_TIME_OUT,int backlog = DEFAULT_BACK_LOG);
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