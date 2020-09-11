#pragma once

typedef int(*ReadSock)(void *SockHandle,uint8_t* buf,uint32_t bufSize);
typedef int(*WriteSock)(void *SockHandle,uint8_t* buf, uint32_t bufSize);
typedef int(*CloseSock)(void *SockHandle);

struct SocketOperation
{
	void *handle;
	ReadSock read;
	WriteSock write;
	CloseSock close;
};

class IEvent
{
protected:
	IEvent() = default;
	virtual ~IEvent() = default;
public:
	virtual int ConnectEvent(SocketOperation* call) = 0;
	virtual int DisConnectEvent(SocketOperation* call) = 0;
	virtual int ReadBuffEvent(SocketOperation* call) = 0;
	virtual int WriteBuffEvent(SocketOperation* call) = 0;
	virtual int SocketErrEvent(SocketOperation* call) = 0;
};
