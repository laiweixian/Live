#pragma once

#include "stdafx.h"
#include "Network/SocketIO.h"
#include "Rtmp/RtmpApp/RtmpClients/ClientManager.h"
#include "Rtmp/RtmpApp/RtmpRoom/RoomManager.h"

#define DECLARE_RTMP_APP struct Optional{string name;string ip;int port;uint32_t chunkSize;};
	

class CRtmpApp : public CSocketIO,
				 public CClientManager,
				 public CRtmpRoomManager
{
public:
	DECLARE_RTMP_APP
	CRtmpApp(Optional appOpt);
	~CRtmpApp();
public:
	

protected:

	string GetAppName() ;
	uint32_t GetChunkSize();

	CClientManager*   GetClientManager() ;
	CRtmpRoomManager* GetRoomManager();
	CSocketIO*		  GetSocketIO();
private:
	Optional m_Option;
};
