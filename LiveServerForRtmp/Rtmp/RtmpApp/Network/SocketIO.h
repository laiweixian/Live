#pragma once

#include "stdafx.h"

#define SOCKET_OK	0	
#define ERROR_SOCK_INIT	-1
#define ERROR_SOCK_CREATE -2
#define ERROR_SOCK_NON_BLOCAK	-3
#define ERROR_SOCK_BIND	-4
#define ERROR_SOCK_LISTEN	-5	

#define DECLARE_SOCKET_EVENT	\
		struct Optional{		\
			char ip[100];		\
			int port;			\
			int backlog;		\
			int timeout;		\
			int maxConnect;};

#define DECLARE_CONNECTER		\
	struct Connecter{int ioid;	\
					 SOCKET sock;\
					 sockaddr_in addr;};

class ISocketEvent
{
protected:
	ISocketEvent() = default;
	virtual ~ISocketEvent() = default;

public:
	virtual	void OnConnect(const int ioID) = 0;
	virtual void OnReceive(const int ioID)= 0;
	virtual void OnClose(const int ioID) = 0;
	virtual void OnError(const int ioID,const int errorCode) = 0;
};

class ISocket {
public:
	DECLARE_SOCKET_EVENT
	ISocket(ISocketEvent *pEvent);
	~ISocket();

public:
	virtual int Open(ISocket::Optional opti) = 0;
	virtual void Loop() = 0;
	virtual int Read(const int ioID,const void *src,size_t size) = 0;
	virtual int Write(const int ioID,const void *src, size_t size) = 0;
	virtual int Close(const int ioID) =0;
	
protected:
	ISocketEvent *m_Event;
	ISocket::Optional m_Optional;
};

class CSocketIO : public ISocket
{
public:
	CSocketIO(ISocketEvent *pEvent);
	~CSocketIO();

	//ISocket
	int Open(ISocket::Optional opti) ;
	int Read(const int ioID, const void *src, size_t size);
	int Write(const int ioID, const void *src, size_t size);
	int Close(const int ioID) ;
	void Loop();

private:
	static int SetSocketNonblock(SOCKET sock);
	int CheckConnect();
	int CheckReceive();

	void CloseSocketServer();
	int GenIOID();
private:
	DECLARE_CONNECTER
	
	SOCKET m_ListSock;
	ISocket::Optional m_Optional;
	vector<Connecter*> m_Connecters;
};
