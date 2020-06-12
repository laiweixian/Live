#include "RtmpApp.h"

CRtmpApp::CRtmpApp(AppOptional appOpt): m_IO(this),m_Option(appOpt)
{

}

CRtmpApp::~CRtmpApp()
{

}

void CRtmpApp::PreInit()
{

}
void CRtmpApp::Init()
{

}
void CRtmpApp::Run()
{

}

//ISocketEvent
void CRtmpApp::OnConnect(const int ioID)
{

}

void CRtmpApp::OnReceive(const int ioID)
{

}

void CRtmpApp::OnClose(const int ioID)
{

}

void CRtmpApp::OnError(const int ioID, const int errorCode)
{

}
