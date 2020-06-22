#include "ClientManager.h"
#include "Rtmp/RtmpApp/Network/SocketIO.h"

CClientManager::CClientManager(uint32_t chunkSize):m_ChunkSize(chunkSize)
{

}

CClientManager::~CClientManager()
{

}

int CClientManager::Connect(CSocketClient *pClient)
{
	CRtmpClient *pNew = NULL;

	pNew = new CRtmpClient(m_ChunkSize,pClient,GetInstanceManager());
	m_Clients.push_back(pNew);
	return 0;
}

int CClientManager::DisConnect(CSocketClient *pClient)
{
	auto it = m_Clients.begin();
	
	for (it = m_Clients.begin(); it!= m_Clients.end();it++)
	{
		if ((*it)->GetClietnIo() == pClient)
			(*it)->OnDisConnct();
	}
	return 0;
}	

int CClientManager::Receive(CSocketClient *pClient)
{
	auto it = m_Clients.begin();

	for (it = m_Clients.begin(); it != m_Clients.end();it++)
	{
		if ((*it)->GetClietnIo() == pClient)
			(*it)->OnReceive();
	}
	return 0;
}

int CClientManager::SocketErr(CSocketClient *pClient)
{
	auto it = m_Clients.begin();

	for (it = m_Clients.begin(); it != m_Clients.end();it++)
	{
		if ((*it)->GetClietnIo() == pClient)
			(*it)->OnSockErr();
	}
	return 0;
}

int CClientManager::PreInitialize()
{
	return 0;
}

int CClientManager::Initialize()
{
	GetSocketIO()->RegisterEvent(this);
	return 0;
}

int CClientManager::Run()
{
	return 0;
}

int CClientManager::Pause()
{
	return 0;
}

int CClientManager::Stop()
{
	return 0;
}
