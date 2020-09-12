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
	return -1;
}	

int CRtmp::Run()
{
	return -1;
}

int CRtmp::OnConnect(void* handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnDisConnect(void* handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnReceive(void* handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnSend(void* handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::OnError(void* handle, ISocketOperation* iop)
{
	return -1;
}

int CRtmp::WriteOperation(const void *pUser, uint8_t* buf, uint32_t length)
{
	return -1;
}

int CRtmp::CloseOperation(const void *pUser, uint8_t* buf, uint32_t length)
{
	return -1;
}



