#include "Rtmp.h"

#define  DEFALUT_APP_NAME  "live"
#define  DEFALUT_IP			"127.0.0.1"
#define  DEFALUT_PORT		1937

CRtmp::CRtmp() 
{
	m_File = new CSocketIO(this,DEFALUT_IP,DEFALUT_PORT);
	m_Client = new CClientManager();
}

CRtmp::~CRtmp()
{

}

int CRtmp::Initialize()
{

	return 0;
}	

int CRtmp::OnConnect(void* handle, ISocketOperation* iop)
{

}
int CRtmp::OnDisConnect(void* handle, ISocketOperation* iop)
{

}
int CRtmp::OnReceive(void* handle, ISocketOperation* iop)
{

}
int CRtmp::OnSend(void* handle, ISocketOperation* iop)
{

}
int CRtmp::OnErr(void* handle, ISocketOperation* iop)
{

}



