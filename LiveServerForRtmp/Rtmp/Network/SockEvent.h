#pragma once

typedef int(*ReadSock)(void *SockHandle,uint8_t* buf,uint32_t bufSize);
typedef int(*WriteSock)(void *SockHandle,uint8_t* buf, uint32_t bufSize);
typedef int(*CloseSock)(void *SockHandle);

class ISocketOperation
{
protected:
	ISocketOperation() = default;
	virtual ~ISocketOperation() = default;

public:
	virtual int Read(void* handle,uint8_t* buf,uint32_t length) = 0;
	virtual int Write(void* handle, uint8_t* buf, uint32_t length) = 0;
	virtual int Close(void* handle) = 0;
};

class ISocketEvent
{
protected:
	ISocketEvent() = default;
	virtual ~ISocketEvent() = default;
public:
	virtual int OnConnect(void* handle, ISocketOperation* iop) = 0;
	virtual int OnDisConnect(void* handle, ISocketOperation* iop) = 0;
	virtual int OnReceive(void* handle, ISocketOperation* iop) = 0;
	virtual int OnSend(void* handle, ISocketOperation* iop) = 0;
	virtual int OnError(void* handle, ISocketOperation* iop) = 0;
};
