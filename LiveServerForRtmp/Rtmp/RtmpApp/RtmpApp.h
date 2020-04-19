#pragma once

#include "stdafx.h"
#include "Network/SocketIO.h"
#include "RtmpRoom/RtmpRoom.h"

#define DECLARE_RTMP_APP	\
	struct AppOptional{string name;string ip;int port;};

class CRtmpApp : public ISocketEvent
{
public:
	DECLARE_RTMP_APP
	CRtmpApp(AppOptional appOpt);
	~CRtmpApp();

public:	
	//ISocketEvent
	void OnConnect(const int ioID) = 0;
	void OnReceive(const int ioID) = 0;
	void OnClose(const int ioID) = 0;
	void OnError(const int ioID, const int errorCode) = 0;

private:
	CRtmpApp::AppOptional m_Option;
	CSocketIO			  m_IO;

	
};
