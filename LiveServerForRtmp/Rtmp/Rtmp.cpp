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
	CRtmpApp::Optional optional;
	optional.name = DEFALUT_APP_NAME;
	optional.ip = DEFALUT_IP;
	optional.port = DEFALUT_PORT;

	m_App = new CRtmpApp(optional);
	
}	

void CRtmp::Init()
{
	m_App->InitApp();
}

void CRtmp::Run()
{
	while (1)
	{
		m_App->RunApp();
	}
}


