#include "ClientManager.h"


CClientManager::CClientManager()
{

}

CClientManager::~CClientManager()
{

}

int CClientManager::Connect(CSocketClient *pClient)
{
	CRtmpClient *pNew = NULL;

	pNew = new CRtmpClient(GetAppName(),GetChunkSize(),pClient);
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

