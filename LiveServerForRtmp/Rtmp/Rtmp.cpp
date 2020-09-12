#include "Rtmp.h"

#define  DEFALUT_APP_NAME  "live"
#define  DEFALUT_IP			"127.0.0.1"
#define  DEFALUT_PORT		1937
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
	m_File->Run();
	m_Client->Run();
	return 0;
}

int CRtmp::OnConnect(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnDisConnect(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnReceive(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnSend(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnError(SOCKET_HANDLE handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::WriteForHandle(const IO_HANDLE handle, uint8_t* buf, uint32_t length)
{
	return -1;
}
int CRtmp::CloseForHandle(const IO_HANDLE handle)
{
	return -1;
}


