#pragma once

#include "stdafx.h"
#include "Network/SocketIO.h"
#include "Rtmp/RtmpApp/RtmpClients/ClientManager.h"
#include "Rtmp/RtmpApp/RtmpInstance/InstanceManager.h"

#define DECLARE_RTMP_APP struct Optional{string name;string ip;int port;uint32_t chunkSize;};
	

class CRtmpApp : public CSocketIO,
				 public CClientManager,
				 public CInstanceManager
{
public:
	DECLARE_RTMP_APP
	CRtmpApp(Optional appOpt);
	~CRtmpApp();
public:
	int PreInitialize();
	int Initialize();
	int Run();
	int Pause();
	int Stop();

protected:

	uint32_t GetChunkSize();

	CClientManager*   GetClientManager() ;
	CInstanceManager* GetInstanceManager();
	CSocketIO*		  GetSocketIO();
private:
	Optional m_Option;
};
