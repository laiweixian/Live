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

int CRtmp::PreInitialize()
{
	CRtmpApp::Optional optional;
	optional.name = DEFALUT_APP_NAME;
	optional.ip = DEFALUT_IP;
	optional.port = DEFALUT_PORT;
	optional.chunkSize = 128;

	m_App = new CRtmpApp(optional);
	m_App->PreInitialize();
	return 0;
}	

int CRtmp::Initialize()
{
	m_App->Initialize();
	return 0;
}

int CRtmp::Run()
{
	while (1)
	{
		m_App->Run();
	}
	return 0;
}

int CRtmp::Pause()
{
	return 0;
}

int CRtmp::Stop()
{
	return 0;
}


