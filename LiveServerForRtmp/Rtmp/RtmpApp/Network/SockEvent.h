#pragma once
#include "SocketClient.h"

class ISocketEvent
{
protected:
	ISocketEvent() = default;
	virtual ~ISocketEvent() = default;
public:
	virtual int Connect(CSocketClient *pClient) = 0;
	virtual int DisConnect(CSocketClient *pClient) = 0;
	virtual int Receive(CSocketClient *pClient) = 0;
	virtual int SocketErr(CSocketClient *pClient) = 0;
};
