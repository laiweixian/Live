#pragma once

typedef int(*ReadSock)(void *SockHandle,uint8_t* buf,uint32_t bufSize);
typedef int(*WriteSock)(void *SockHandle,uint8_t* buf, uint32_t bufSize);
typedef int(*CloseSock)(void *SockHandle);

typedef void* SOCKET_HANDLE;

class ISocketOperation
{
protected:
	ISocketOperation() = default;
	virtual ~ISocketOperation() = default;

public:
	virtual int Read(SOCKET_HANDLE handle,uint8_t* buf,uint32_t length) = 0;
	virtual int Write(SOCKET_HANDLE handle, uint8_t* buf, uint32_t length) = 0;
	virtual int Close(SOCKET_HANDLE handle) = 0;
};

class ISocketEvent
{
protected:
	ISocketEvent() = default;
	virtual ~ISocketEvent() = default;
public:
	virtual int OnConnect(SOCKET_HANDLE handle,ISocketOperation* iop) = 0;
	virtual int OnDisConnect(SOCKET_HANDLE handle,ISocketOperation* iop) = 0;
	virtual int OnReceive(SOCKET_HANDLE handle,ISocketOperation* iop) = 0;
	virtual int OnSend(SOCKET_HANDLE handle,ISocketOperation* iop) = 0;
	virtual int OnError(SOCKET_HANDLE handle,ISocketOperation* iop) = 0;
};
