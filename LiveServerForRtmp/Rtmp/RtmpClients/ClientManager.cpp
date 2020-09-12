#include "ClientManager.h"
#include "Rtmp/Network/SocketIO.h"

CClientManager::CClientManager(uint32_t chunkSize,  IClientOperation* oPera):\
					m_DefaultChunkSize(chunkSize),m_Operation(oPera)
{

}

CClientManager::~CClientManager()
{

}

void CClientManager::Processing(const void* pUser, uint8_t* buf, const uint32_t length)
{
	
	
	
}

void CClientManager::Enter(const void* pUser)
{
	Client cli;
	CRtmpClient *pClient = NULL;
	auto it = m_Clients.begin();

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		if (it->pUser == pUser)
			return;
	}

	pClient = new CRtmpClient(m_DefaultChunkSize,this);
	cli.pUser = pUser;
	cli.pClient = pClient;

	m_Clients.push_back(cli);
}

void CClientManager::Leave(const void* pUser)
{

}
