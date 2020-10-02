#include "Rtmp.h"

#define  DEFALUT_APP_NAME  "live"
#define  DEFALUT_IP			"127.0.0.1"
#define  DEFALUT_PORT		1935
#define  DEFALUT_CHUNK_SIZE 128



CRtmp::CRtmp() 
{
	m_File = new CSocketIO(this,DEFALUT_IP,DEFALUT_PORT);
	m_Client = new CClientManager(DEFALUT_CHUNK_SIZE,this);
}

CRtmp::~CRtmp()
{

}

int CRtmp::Initialize()
{
	int ret = 0;
	m_File->Initialize();
	m_Client->Initialize();
	return 0;
}	

int CRtmp::Run()
{
	while (1)
	{
		m_File->Run();
		m_Client->Run();
	}
	
	return 0;
}

int CRtmp::OnConnect(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	auto it = m_Users.begin();
	SockUser *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (*it);
		if (pUser->handle == handle)
			return 0;
	}

	pUser = new SockUser;
	pUser->handle = handle;
	pUser->ioOp = iop;
	m_Users.push_back(pUser);

	m_Client->Enter(pUser);
	return 0;
}

int CRtmp::OnDisConnect(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	auto it = m_Users.begin();
	SockUser *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (*it);
		if (pUser->handle == handle)
		{
			m_Client->Leave(pUser);
			m_Users.erase(it);
		}
	}

	return 0;
}

int CRtmp::OnReceive(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	auto it = m_Users.begin();
	SockUser *pUser = NULL;
	uint8_t *buf = NULL; 
	uint32_t length = 0;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (*it);
		if (pUser->handle == handle)
		{
			length = pUser->ioOp->Read(pUser->handle, NULL, 0);
			buf = new uint8_t[length];
			pUser->ioOp->Read(pUser->handle, buf, length);

			m_Client->Processing(pUser, buf, length);
		}
	}

	if (buf) delete[] buf;
	buf = NULL;
	return 0;
}

int CRtmp::OnSend(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnError(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return OnDisConnect(handle,iop);
}

int CRtmp::WriteForHandle(const IO_HANDLE handle, uint8_t* buf, uint32_t length)
{
	auto it = m_Users.begin();
	SockUser *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (*it);
		if (pUser == handle)
		{
			return pUser->ioOp->Write(pUser->handle, buf, length);
		}
	}

	return -1;
}

int CRtmp::CloseForHandle(const IO_HANDLE handle)
{
	auto it = m_Users.begin();
	SockUser *pUser = NULL;

	for (it = m_Users.begin(); it != m_Users.end(); it++)
	{
		pUser = (*it);
		if (pUser == handle)
		{
			return pUser->ioOp->Close(pUser->handle);
		}
	}

	return -1;
}


