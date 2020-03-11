#include "Rtmp/RtmpApplication/RtmpApplication.h"


CRtmpApplication::CRtmpApplication(const char* ip,const int port,const char* appName)
{
	
	strcpy(m_AppName, appName);
}

CRtmpApplication::~CRtmpApplication()
{

}

ULONG CRtmpApplication::Init()
{
	
}

ULONG CRtmpApplication::Run()
{
	
}

ULONG CRtmpApplication::Release()
{

}

void CRtmpApplication::OnConnect(const int ioId)
{
	//has new client

}

void CRtmpApplication::OnData(const int ioId)
{

}

void CRtmpApplication::OnClose(const int ioId)
{

}