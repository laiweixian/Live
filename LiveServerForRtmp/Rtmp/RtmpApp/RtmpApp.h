#pragma once

#include "stdafx.h"
#include "Network/SocketIO.h"
#include "RtmpRoom/RtmpRoom.h"

class CRtmpApp 
{
public:
	CRtmpApp(const char* appName,const char* ip,const int port);
	~CRtmpApp();

	void Init();

private:
	CSocketIO *m_IO;
	vector<CRtmpRoom*> m_Rooms;
	CRtmpRoom *m_TempRoom;
};
