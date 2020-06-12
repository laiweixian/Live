#include "Rtmp.h"

#define  DEFALUT_APP_NAME  "live"
#define  DEFALUT_IP			"127.0.0.1"
#define  DEFALUT_PORT		1937

CRtmp::CRtmp() : m_App(NULL)
{

}

CRtmp::~CRtmp()
{

}

void CRtmp::PreInit()
{
	CRtmpApp::AppOptional optional;
	optional.name = DEFALUT_APP_NAME;
	optional.ip = DEFALUT_IP;
	optional.port = DEFALUT_PORT;

	m_App = new CRtmpApp(optional);
	
}	

void CRtmp::Init()
{

}

void CRtmp::Run()
{

}


