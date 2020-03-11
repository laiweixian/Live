#include "Rtmp/Rtmp.h"

CRtmp::CRtmp()
{
	RegisterApplication(new CRtmpApplication(DEFAULT_IP,DEFAULT_PORT,DEFAULT_APP_NAME));
}

CRtmp::~CRtmp()
{

}

void CRtmp::RegisterApplication(CRtmpApplication *pApp)
{
	m_RtmpApps.push_back(pApp);
}

ULONG CRtmp::Init()
{
	ULONG ret = SAR_OK;
	auto it = m_RtmpApps.begin();
	CRtmpApplication *pApp = NULL;

	for (it = m_RtmpApps.begin(); it != m_RtmpApps.end(); it++)
	{
		pApp = (*it);
		ret |= pApp->Init();
	}
	return ret;
}

ULONG CRtmp::Run()
{
	ULONG ret = SAR_OK;
	auto it = m_RtmpApps.begin();
	CRtmpApplication *pApp = NULL;

	for (it = m_RtmpApps.begin(); it != m_RtmpApps.end(); it++)
	{
		pApp = (*it);
		ret |= pApp->Run();
	}
	return ret;
}

ULONG CRtmp::Release()
{
	ULONG ret = SAR_OK;
	auto it = m_RtmpApps.begin();
	CRtmpApplication *pApp = NULL;

	for (it = m_RtmpApps.begin(); it != m_RtmpApps.end(); it++)
	{
		pApp = (*it);
		ret |= pApp->Release();
	}
	return ret;
}