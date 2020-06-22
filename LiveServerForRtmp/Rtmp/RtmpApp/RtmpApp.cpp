#include "RtmpApp.h"

CRtmpApp::CRtmpApp(Optional appOpt): m_Option(appOpt),\
									CSocketIO(appOpt.ip.data(),appOpt.port),\
									CClientManager(appOpt.chunkSize),\
									CInstanceManager(appOpt.name)
{

}

CRtmpApp::~CRtmpApp()
{

}

int CRtmpApp::PreInitialize()
{
	CSocketIO::PreInitialize();
	CClientManager::PreInitialize();
	CInstanceManager::PreInitialize();
	return 0;
}	

int CRtmpApp::Initialize()
{
	CSocketIO::Initialize();
	CClientManager::Initialize();
	CInstanceManager::Initialize();
	return 0;
}

int CRtmpApp::Run()
{
	CSocketIO::Run();
	CClientManager::Run();
	CInstanceManager::Run();
	return 0;
}

int CRtmpApp::Pause()
{
	CSocketIO::Pause();
	CClientManager::Pause();
	CInstanceManager::Pause();
	return 0;
}	

int CRtmpApp::Stop()
{
	CSocketIO::Stop();
	CClientManager::Stop();
	CInstanceManager::Stop();
	return 0;
}

CClientManager* CRtmpApp::GetClientManager()
{
	return this;
}

CInstanceManager* CRtmpApp::GetInstanceManager()
{
	return this;
}

CSocketIO* CRtmpApp::GetSocketIO()
{
	return this;
}


uint32_t CRtmpApp::GetChunkSize()
{
	return m_Option.chunkSize;
}






