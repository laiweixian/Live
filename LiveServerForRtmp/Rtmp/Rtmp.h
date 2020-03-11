#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApplication/RtmpApplication.h"

#define DEFAULT_IP	"0.0.0.0"
#define DEFAULT_PORT 1935
#define DEFAULT_APP_NAME	"lwx"

class CRtmp
{
public:
	CRtmp();
	~CRtmp();

	ULONG Init();
	ULONG Run();
	ULONG Release();
private:
	void RegisterApplication(CRtmpApplication *pApp);
private:

	vector<CRtmpApplication*> m_RtmpApps;
};