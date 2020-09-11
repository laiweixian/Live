#pragma once

#include "stdafx.h"
#include "RtmpApp/RtmpApp.h"
#include "Network/SocketIO.h"
#include "RtmpClients/ClientManager.h"

class CRtmp : public CRtmpApp,
			  public CClientManager
{
public:
	CRtmp();
	~CRtmp();
public:
	int Initialize();
	int Run();
private:
	CSocketIO *pSocket
};