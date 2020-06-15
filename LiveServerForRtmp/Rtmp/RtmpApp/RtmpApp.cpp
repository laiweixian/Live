#include "RtmpApp.h"

CRtmpApp::CRtmpApp(Optional appOpt): m_Option(appOpt),CSocketIO(appOpt.ip.data(),appOpt.port)
{

}

CRtmpApp::~CRtmpApp()
{

}

int CRtmpApp::InitApp()
{
	CSocketIO::SocketInit();
	CClientManager::ClientManagerInit();
	CRtmpRoomManager::RoomManagerInit();
	return 0;
}

int CRtmpApp::RunApp()
{
	CheckEvent();
	return 0;
}

CClientManager* CRtmpApp::GetClientManager()
{
	return this;
}

CRtmpRoomManager* CRtmpApp::GetRoomManager()
{
	return this;
}

CSocketIO* CRtmpApp::GetSocketIO()
{
	return this;
}

string CRtmpApp::GetAppName()
{
	return m_Option.name;
}

uint32_t CRtmpApp::GetChunkSize()
{
	return m_Option.chunkSize;
}






