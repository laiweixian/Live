#pragma once

#include "stdafx.h"

#include "SocketIO/SocketIO.h"
#include "Rtmp/RtmpApplication/RtmpRoom/RtmpRoom.h"


class CRtmpApplication : public CIOMessage
{
public:
	CRtmpApplication(const char* ip, const int port, const char* appName);
	~CRtmpApplication();

	ULONG Init();
	ULONG Run();
	ULONG Release();

	
public:
	//CIOMessage
	void OnConnect(const int ioId);
	void OnData(const int ioId);
	void OnClose(const int ioId);

private:
	char m_AppName[200];

	vector<CRtmpRoom*> m_Rooms;
	vector<CRtmpUser*> m_TempUser;
};
