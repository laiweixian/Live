#include "ClientManager.h"
#include "Rtmp/Network/SocketIO.h"

#define APP_NAME	"live"

CClientManager::CClientManager(uint32_t chunkSize, IIOOperation* oPera):\
					m_DefaultChunkSize(chunkSize),m_Operation(oPera)
{
	string name(APP_NAME);
	m_App = new CRtmpApp(name);
}

CClientManager::~CClientManager()
{
	auto it = m_Clients.begin();
	Client cli;
	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		cli = *it;
		cli.handle = NULL;
		delete cli.pClient;
		cli.pClient = NULL;
	}
	m_Clients.clear();

	delete m_App;
	m_App = NULL;
}

int CClientManager::Initialize()
{
	m_App->Initialize();
	return 0;
}

int CClientManager::Run()
{
	m_App->Run();
	return 0;
}

void CClientManager::Processing(const IO_HANDLE handle, uint8_t* buf, const uint32_t length)
{
	auto it = m_Clients.begin();

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		if (it->handle == handle)
			it->pClient->Processing(buf, length);
	}

	return;
}

void CClientManager::Enter(const IO_HANDLE handle)
{
	Client cli;
	CRtmpClient *pClient = NULL;
	auto it = m_Clients.begin();

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		if (it->handle == handle)
			return;
	}

	pClient = new CRtmpClient(m_DefaultChunkSize,this);
	cli.handle = handle;
	cli.pClient = pClient;

	m_Clients.push_back(cli);
	return;
}

void CClientManager::Leave(const IO_HANDLE handle)
{
	auto it = m_Clients.begin();
	Client pClient ;

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		pClient = *it;
		if (pClient.handle == handle)
		{
			m_Clients.erase(it);
		}
	}

	return ;
}


int CClientManager::WriteToUser(CRtmpClient* pClient, uint8_t* buf, const uint32_t length)
{
	auto it = m_Clients.begin();
	Client cl;

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		cl = *it;
		if (cl.pClient == pClient)
		{
			return m_Operation->WriteForHandle(cl.handle, buf, length);
		}
	}

	return -1;
}

int CClientManager::CloseUser(CRtmpClient* pClient)
{
	auto it = m_Clients.begin();
	Client cl;

	for (it = m_Clients.begin(); it != m_Clients.end(); it++)
	{
		cl = *it;
		if (cl.pClient == pClient)
		{
			return m_Operation->CloseForHandle(cl.handle);
		}
	}

	return -1;
}